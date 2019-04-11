#!/usr/bin/tcc -run
#include "main.h"
#include <sys/types.h>
#ifdef _WIN32
#include <windows.h>
#include <winsock.h>
#elif unix
#include <sys/ipc.h>
#include <sys/msg.h>
#endif

#define MSGQID 80

typedef struct
{
	long mtype;
	char mtext[256];
}msgbuf;
int unitTestStateMachine();
int main()
{
	LOGFN;

	msgbuf message = (msgbuf){.mtype=1,.mtext={0,}};
	size_t szMsgText = sizeof(message.mtext);

	key_t ipcKey = ftok("ipc.ftok",MSGQID);
	msgsnd(MSGQID, &message, szMsgText,IPC_NOWAIT);
	printf("ipcKey:%d\n",msgget(ipcKey,IPC_CREAT));

	return 0;
}

int unitTestStateMachine()
{
	int errCnt=0;
	message_t request = {MY_PUID,MSG_HELLO};
	errCnt += pushMsg(request);
	errCnt += request.message = MSG_HOLA;
	errCnt += pushMsg(request);
	errCnt += request.message = MSG_FOO;
	errCnt += pushMsg(request);
	errCnt += request.message = MSG_HOLA;
	errCnt += pushMsg(request);
	errCnt += _rollMsgQueue();
	errCnt += request.message = MSG_HELLO;
	errCnt += pushMsg(request);
	errCnt += request.message = MSG_RUN;
	errCnt += pushMsg(request);
	errCnt += request.message = MSG_FINISH;
	errCnt += pushMsg(request);
	errCnt += request.message = MSG_RESET;
	errCnt += pushMsg(request);
	errCnt += request.message = MSG_STOP;
	errCnt += pushMsg(request);
	errCnt += _rollMsgQueue();
	return errCnt ? E_ERR : E_OK;
}
