#include <stdlib.h>
#include <stdio.h>
//#include <unistd.h>

#define GENLBL(x)    { x, #x }

#define MY_PUID 1999
#define TIER_PUID 50

#define LOGFN (printf("%s()\n",__FUNCTION__))
#define MA_NO_ACTION NULL
#define MA_IGN_ST 0
#define MA_IGN_CTX 0
#define MA_IGN_SRC 0

#define CTX_UNKNOWN 0xFF
#define CTX_INIT 0
#define CTX_RUN 1
#define CTX_END 2

#define E_OK 0
#define E_ERR 1

#define EMPTY_MSG (message_t){0,0,0}
#define EMPTY_ACTION (action_t){0,0,0,0,0,0}

#define MSG_UNKNOWN 0xFF
#define MSG_HELLO 	0x01
#define MSG_RUN 	0x02
#define MSG_STOP 	0x03
#define MSG_HOLA 	0x04
#define MSG_RESET	0x05
#define MSG_FINISH	0x06

#define MAX_MSG 6

typedef struct
{
   int         iLbl;
   const char *pszLbl;
} genlbl_t;

typedef struct
{
	int src,message,args;
}message_t;
typedef struct
{
	int src,message,state,newstate,newctx;
	int(*pfn)(int);
}action_t;

enum ctx_index
{
	init,run,end
};

static const genlbl_t PUIDLBL[]=
{
	GENLBL(MY_PUID),
	GENLBL(TIER_PUID)
};
static const genlbl_t MSGLBL[]=
{
	GENLBL(MSG_UNKNOWN),
	GENLBL(MSG_HELLO),
	GENLBL(MSG_RUN),
	GENLBL(MSG_STOP),
	GENLBL(MSG_HOLA),
	GENLBL(MSG_RESET),
	GENLBL(MSG_FINISH)
};
static const genlbl_t CTXLBL[]=
{
	GENLBL(CTX_UNKNOWN),
	GENLBL(CTX_INIT),
	GENLBL(CTX_RUN),
	GENLBL(CTX_END)
};
const char* getLbl(const int id, const genlbl_t* lbl_array);
const char* getMsgLbl(const int id);
const char* getCtxLbl(const int id);
const char* getPuidLbl(const int id);
//public
int pushMsg(message_t msg);
//private 
int findNewContext();
const action_t* _findActionInCtx(const action_t* ctx, const int msgId);
void _setNewCurCtx(int newctx);
int _processMsg();
void _dropLastMsgFromQueue();
int _appendOnQueue(message_t newMsg);
int _nextSlotOnQueue();
//passe en revue toute la file de message
//retourne le nombre d'actions exécutés
int _rollMsgQueue();

//fonctions du module
int hello() { LOGFN;return E_OK; }
int hola() { LOGFN;return E_OK; }
int start() { LOGFN;return E_OK; }
int reset() { LOGFN;return E_OK; }
int finish() { LOGFN;return E_OK; }
