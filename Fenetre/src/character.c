#include <SDL2/SDL.h>
#include <stdlib.h>
#include <assert.h>
#include "character.h"

static Character m_chList[MAX_CH];
static int m_chLoaded=0;

Character* character_Init(char* pszFilePath)
{
	Character cha;
	printf("new character: %d/%d\n",m_chLoaded+1,MAX_CH);
	if(m_chLoaded >= MAX_CH)
	{
		printf("Error : Too much character loaded\n");
	}
	cha.fg = foreground_Load(pszFilePath);
	cha.dir = E;
	cha.bhv = standing;
	//m_fgList[m_fgIndex].pSprite = getLastSprite();
	m_chList[m_chLoaded] = cha;
	m_chLoaded++;
	return &(m_chList[m_chLoaded-1]);
}	
void character_DestroyAll()
{
	m_chLoaded--;
	while(m_chLoaded>=0)
	{
		sprite_Destroy(&(m_chList[m_chLoaded].fg.sprite));
		m_chLoaded--;
	}
}
void character_Destroy(Character* pCh)
{
	sprite_Destroy(&(pCh->fg.sprite));
	//assert(NULL == pCh->fg.sprite);
}
void character_Kill(Character* pCh)
{
	printf("%s has been killed\n",pCh->name);
	character_Destroy(pCh);
}
Character* getCh(byte_t b)
{
	return &(m_chList[b]);
}
