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
void character_copyToRender(Character* ch)
{
	foreground_copyToRender(&ch->fg);
}
	
void character_setDirection(Character* pCh,const byte_t dirMask)
{
	//TODO: c'est la dernière touche enfoncé qui doit induire le mouvement
	//static byte_t lastDirMask;
	pCh->bhv=moving;
	switch(dirMask) //UP,DOWN,LEFT,RIGHT -> 0bUDLR
	{
		//orthos
		case 8: pCh->dir=N; break;
		case 4: pCh->dir=S; break;
		case 2: pCh->dir=W; break;
		case 1: pCh->dir=E; break;
		//diags
		case 5: pCh->dir=SE; break;
		case 6: pCh->dir=SW; break;
		case 9: pCh->dir=NE; break;
		case 10: pCh->dir=NW; break;
		//misc
		case 7: pCh->dir=S; break;
		case 11: pCh->dir=N; break;
		case 13: pCh->dir=E; break;
		case 14: pCh->dir=W; break;
		
		default :
		pCh->bhv = standing;
		break;
	}
	//lastDirMask = dirMask;
}
void character_move(Character* pCh)
{
	const float qPi = 0.7853; //un pas diagonal vaut un quart de pi sur x et y
	const int pas = 10; //10 pixels par pas sinon les diagonales sont trop  carrés
	const int pasDiag = qPi * pas;
	SDL_Rect* pPos = &(pCh->fg.dstRect);
	switch(pCh->dir)
	{
		case E: pPos->x+=pas; break;
		case W: pPos->x-=pas; break;
		case S: pPos->y+=pas; break;
		case N: pPos->y-=pas; break;
		case SE:
		pPos->x += pasDiag;
		pPos->y += pasDiag;
		break;
		case SW:
		pPos->x -= pasDiag;
		pPos->y += pasDiag;
		break;
		case NE:
		pPos->x += pasDiag;
		pPos->y -= pasDiag;
		break;
		case NW:
		pPos->x -= pasDiag;
		pPos->y -= pasDiag;
		break;
	}
	//printf("x:%d y:%d\n",pPos->x,pPos->y); 
}
