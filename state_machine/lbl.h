#include <stdlib.h>
#include <stdio.h>
#include "mod_const.h"

#define GENLBL(x)    { x, #x }

typedef struct
{
   int         iLbl;
   const char *pszLbl;
} genlbl_t;

static const genlbl_t MSGLBL[]=
{
	GENLBL(MSG_UNKNOWN),
	GENLBL(MSG_HELLO),
	GENLBL(MSG_RUN),
	GENLBL(MSG_STOP),
	GENLBL(MSG_HOLA),
	GENLBL(MSG_RESET),
	GENLBL(MSG_FINISH),
	GENLBL(MSG_FOO)
};

static const genlbl_t PUIDLBL[]=
{
	GENLBL(MY_PUID),
	GENLBL(TIER_PUID)
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

//lbl.c
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
