#include <stdlib.h>
#include <assert.h>
#include "foreground.h"

static Foreground m_fgList[MAX_FG];
static int m_fgIndex=0;
Foreground* foreground_Load(const char* pszFilePath)
{
	Foreground* pFg;
	if(m_fgIndex >= MAX_FG-1)
	{
		printf("Error : Too much sprite at foreground\n");
	}
	//sprite_Load(pszFilePath);
	m_fgList[m_fgIndex].pSprite = sprite_Load(pszFilePath);
	//m_fgList[m_fgIndex].pSprite = getLastSprite();
	pFg = (Foreground*) &(m_fgList[m_fgIndex]);
	m_fgIndex++;
	return pFg;
}
Foreground* getFg(const size_t index)
{
	return &(m_fgList[index]);
}
