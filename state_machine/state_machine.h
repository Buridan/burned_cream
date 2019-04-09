#include "lbl.h"

#define MAX_MSG 6

typedef struct
{
	int src,message,args;
}message_t;

//public
int pushMsg(message_t msg);
//private 
const action_t* _findActionInCtx(const action_t* ctx, const int msgId);
void _setNewCurCtx(int newctx);
int _processMsg();
void _dropLastMsgFromQueue();
int _appendOnQueue(message_t newMsg);
int _nextSlotOnQueue();
//passe en revue toute la file de message
//retourne le nombre d'actions exécutés
int _rollMsgQueue();

//state_machine.c
static enum ctx_index m_curCtx = init;
static int m_MsgIndex = 0;
static message_t m_MsgQueue[MAX_MSG];

int pushMsg(message_t msg)
{
	printf("Message sent by: %s(%d), msg: %s(%d)\n",getPuidLbl(msg.src), msg.src, getMsgLbl(msg.message),msg.message);
	return _appendOnQueue(msg);
}
int _processMsg()
{
	const message_t msg = m_MsgQueue[m_MsgIndex];
	if(msg.message==EMPTY_MSG.message)//no message to process
	{
		printf("no message in slot\n");
		return E_ERR;
	}
	//process in current context
	const action_t* isInCtx = _findActionInCtx(m_ctxt_list[m_curCtx], msg.message);
	if(NULL != isInCtx)
	{
		isInCtx->pfn(msg.args);
		_setNewCurCtx(isInCtx->newctx);
		return E_OK;
	}
	//else process with static context
	const action_t* isInCtxStatic = _findActionInCtx(ctxt_static, msg.message);
	if(NULL == isInCtxStatic)
	{
		printf("No message found in static context for %s(%d)\n",getMsgLbl(msg.message),msg.message);
		return E_ERR;
	}
	else
	{
		isInCtxStatic->pfn(msg.args);
		_setNewCurCtx(isInCtxStatic->newctx);
		return E_OK;
	}
}
const action_t* _findActionInCtx(const action_t* ctx, const int msgId)
{
	int i;
	for(i=0;ctx[i].message!=0;i++)
	{
		if(ctx[i].message==msgId || ctx[i].message==0)
		{
			printf("ctx: %s(%d), message:%s(%d)\n",getCtxLbl(m_curCtx), m_curCtx, getMsgLbl(ctx[i].message),ctx[i].message);
			return &ctx[i];
		}
	}
	return NULL;
}
int _appendOnQueue(message_t newMsg)
{
	int i;
	for(i=m_MsgIndex;i!=(m_MsgIndex+MAX_MSG);i++)
	{
		if(m_MsgQueue[i%MAX_MSG].message == 0)
		{
			m_MsgQueue[i] = newMsg;
			return E_OK;
		}
	}
	printf("Message Queue is full\n");
	return E_ERR;
}
int _nextSlotOnQueue() 
{
	m_MsgIndex = (1+m_MsgIndex) % MAX_MSG;
	return m_MsgIndex;
}
int _clearSlotOnQueue(int slotNumber)
{
	m_MsgQueue[slotNumber] = EMPTY_MSG;
	return E_OK;
}
void _setNewCurCtx(int newctx)
{
	if(newctx != m_curCtx || newctx != MA_IGN_CTX)
	{
		printf("switching context from: %s(%d), to: %s(%d)\n",getCtxLbl(m_curCtx),m_curCtx,getCtxLbl(newctx),newctx);
		m_curCtx = newctx;
	}
}
int _rollMsgQueue()
{
	int i;
	int nbActions=0;
	LOGFN;
	for(i=0;i<MAX_MSG;i++)
	{
		printf("[%d/%d]\t",m_MsgIndex+1,MAX_MSG);
		if(E_OK == _processMsg())
		{
			nbActions++;
			_clearSlotOnQueue(m_MsgIndex);
		}
		_nextSlotOnQueue(); 
		printf("\r");
	}
	printf("message processed:%d\n",nbActions);
	return nbActions;
}
void monitorMsgThreadLoad(int actionsParTour)
{
	if(0 == actionsParTour)
	{
		printf("la liste de message est vide\n");
		//sleep(1);//diminue l'attente active
	}
}
