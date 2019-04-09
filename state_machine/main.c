#!tcc -run
#include "main.h"

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

