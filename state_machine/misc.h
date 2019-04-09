#include "base.h"

#define LOGFN (printf("%s()\n",__FUNCTION__))
#define DUMMYFN(f)	int f(){LOGFN;return E_OK;}

//fonctions du module
//int hello() { LOGFN;return E_OK; }
DUMMYFN(hello)
DUMMYFN(hola)
DUMMYFN(start)
DUMMYFN(finish)
DUMMYFN(reset)
DUMMYFN(foo)
