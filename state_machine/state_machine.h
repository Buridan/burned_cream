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

