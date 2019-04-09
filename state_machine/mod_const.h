#include "misc.h"

//identifiants du module
#define MY_PUID 1999
#define TIER_PUID 50

//messages
#define MSG_UNKNOWN 0xFF
#define MSG_HELLO 	0x01
#define MSG_RUN 		0x02
#define MSG_STOP 		0x03
#define MSG_HOLA 		0x04
#define MSG_RESET		0x05
#define MSG_FINISH	0x06
#define MSG_FOO			0x07

//contextes
#define CTX_UNKNOWN 0xFF
#define CTX_INIT 0
#define CTX_RUN 1
#define CTX_END 2

#define MA_NO_ACTION donothing
#define MA_IGN_ST 0
#define MA_IGN_CTX 0
#define MA_IGN_SRC 0

#define EMPTY_MSG (message_t){0,0,0}
#define EMPTY_ACTION (action_t){0,0,0,0,0,0}

enum ctx_index
{
	init,run,end
};
typedef struct
{
	const int src,message,state,newstate,newctx;
	int(*pfn)(int);
}action_t;

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
const action_t* m_ctxt_list[]=
{
	ctxt_init,
	ctxt_run,
	ctxt_end,
	NULL
};
