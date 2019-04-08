#!tcc -run
#include "ctx.h"
#include <assert.h>

int main()
{
	LOGFN;
	message_t request = {MY_PUID,MSG_HELLO};
	if(E_OK != pushMsg(request))
		printf("error while sending message %d",request.message);
	request.message = MSG_HOLA;
	pushMsg(request);
	request.message = MSG_FOO;
	pushMsg(request);
	request.message = MSG_HOLA;
	pushMsg(request);
	_rollMsgQueue();
	request.message = MSG_HELLO;
	pushMsg(request);
	request.message = MSG_RUN;
	pushMsg(request);
	request.message = MSG_FINISH;
	pushMsg(request);
	request.message = MSG_RESET;
	pushMsg(request);
	_rollMsgQueue();

	return 0;
}

static enum ctx_index m_curCtx = init;
static int m_MsgIndex = 0;
static message_t m_MsgQueue[MAX_MSG];

action_t ctxt_static[]=
{
	{MA_IGN_SRC,	MSG_HELLO,	MA_IGN_ST,	MA_IGN_ST,	MA_IGN_CTX,	hello},
	{MA_IGN_SRC,	MSG_HOLA,		MA_IGN_ST,	MA_IGN_ST,	MA_IGN_CTX,	hola},
	{MA_IGN_SRC,	MSG_FOO,		MA_IGN_ST,	MA_IGN_ST,	MA_IGN_CTX,	foo},
	{0,0,0,0,0,NULL}
};
action_t ctxt_init[]=
{
	{MA_IGN_SRC,	MSG_RUN,		MA_IGN_ST,	MA_IGN_ST,	CTX_RUN		,	start},
	{MA_IGN_SRC,	MSG_STOP,		MA_IGN_ST,	MA_IGN_ST,	MA_IGN_CTX,	MA_NO_ACTION},
	{MA_IGN_SRC,	MSG_HOLA,		MA_IGN_ST,	MA_IGN_ST,	MA_IGN_CTX,	hola},
	{0,0,0,0,0,NULL}

};
action_t ctxt_run[]=
{
	{MA_IGN_SRC, MSG_FINISH,	MA_IGN_ST,	MA_IGN_ST,	CTX_END	, finish},
	{0,0,0,0,0,NULL}
};
action_t ctxt_end[]=
{
	{MA_IGN_SRC, MSG_RESET,	MA_IGN_ST,	MA_IGN_ST,	CTX_INIT	, reset},
	{0,0,0,0,0,NULL}
};
static action_t* m_ctxt_list[]=
{
	ctxt_init,
	ctxt_run,
	ctxt_end,
	NULL
};
int pushMsg(message_t msg)
{
	printf("Message sent by: %s(%d), msg: %s(%d)\n",getPuidLbl(msg.src), msg.src, getMsgLbl(msg.message),msg.message);
	if(E_ERR == _appendOnQueue(msg))//queue is full
	{
		return E_ERR;
	}
	return E_OK;
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
const char* getMsgLbl(const int id)
{
	return getLbl(id,MSGLBL);
}
const char* getCtxLbl(const int id)
{
	return getLbl(id,CTXLBL);
}
const char* getPuidLbl(const int id)
{
	return getLbl(id,PUIDLBL);
}
const char* getLbl(const int id, const genlbl_t* lbl_array)
{
	int i;
	const char* res;
	for(i=0;i<sizeof(lbl_array);i++)
	{
		if(lbl_array[i].iLbl == id)
		{
			res = lbl_array[i].pszLbl;
		}
	}
	return (NULL==res) ? lbl_array[0].pszLbl : res;
}
