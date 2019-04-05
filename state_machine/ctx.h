#include <stdlib.h>
#include <stdio.h>

#define MY_PUID 1999
#define LOGFN (printf("%s()\n",__FUNCTION__))
#define MA_NO_ACTION 0
#define MA_IGN_ST 0
#define MA_IGN_CTX 0
#define MA_IGN_SRC 0

#define E_OK 0
#define E_ERR 1

#define MSG_UNKNOWN 0xFF
#define MSG_HELLO 1

#define MAX_MSG 3

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
	init,end
};

//public
int pushMsg(message_t msg);
//private 
int findNewContext();
int _processMsg();
int hello() {
	printf("coucou\n");;
	return E_OK;
}
