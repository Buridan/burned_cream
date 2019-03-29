#!tcc -run
#include "ctx.h"
#include <assert.h>

int main()
{
	LOGFN;
	message_t request = {MY_PUID,MSG_HELLO};
	pushMsg(request);
	_processMsg();

	return 0;
}

static enum ctx_index m_curCtx = init;
static int m_MsgIndex = 0;
static message_t m_MsgQueue[MAX_MSG];

action_t ctxt_static[]=
{
	{0,0,0,0,0,NULL}
};
action_t ctxt_init[]=
{
	{MA_IGN_SRC,	MSG_UNKNOWN,	MA_IGN_ST,	MA_IGN_ST,	MA_IGN_CTX,	MA_NO_ACTION},
	{MA_IGN_SRC,	MSG_HELLO,		MA_IGN_ST,	MA_IGN_ST,	MA_IGN_CTX,	hello},
	{0,0,0,0,0,NULL}

};
action_t ctxt_end[]={};
static action_t* m_ctxt_list[]=
{
	ctxt_init,
	ctxt_end,
	NULL
};
int pushMsg(message_t msg)
{
	printf("Message received from:%d, msg:%d\n",msg.src,msg.message);
	if(m_MsgIndex>=MAX_MSG)//queue is full
	{
		return E_ERR;
	}
	m_MsgQueue[m_MsgIndex].message = msg.message;
	m_MsgIndex++;
	return E_OK;
}
int _processMsg()
{
	int i;
	if(m_MsgIndex==0)//no message to process
	{
		printf("no message to process\n");
		return E_OK;
	}
	m_MsgIndex--;
	const message_t msg = m_MsgQueue[m_MsgIndex];
	for(i=0;m_ctxt_list[m_curCtx][i].message!=0;i++)
	{
		if(m_ctxt_list[m_curCtx][i].message==msg.message)
		{
			m_ctxt_list[m_curCtx][i].pfn(msg.args);
			m_MsgQueue[m_MsgIndex] = (message_t){0, 0 , 0};
			return E_OK;
		}
	}
	return E_OK;
}
