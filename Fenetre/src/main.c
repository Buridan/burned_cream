#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "main.h"

int main(int argc, char** argv)
{
	window_initAll();
	Background decors;
	Foreground* tigre = foreground_Load("./data/spritesheet.bmp");
	decors.pSprite = sprite_Load("./data/decors.bmp");

	//recuperation des dimensions de la texture
	//texture_info BGInfo={0,0,0,0};

	//SDL_QueryTexture(pTexture, &BGInfo.fmt, &BGInfo.acc, &BGInfo.w, &BGInfo.h);
	//source du sprite
	for(size_t i=0;i<MAX_CLIP_COUNT;i++)
	{
		tigre->pSprite->SrcClip[i] = (SDL_Rect){128 * i,15,tigre->pSprite->Info.w/8,48};
	}

	//destination de depart du sprite
	decors.pSprite->DstClip = winCentered(decors.pSprite->Info);
	tigre->pSprite->DstClip  = (SDL_Rect){0,0,128,48};

	//Copie de la texture dans le rendu
	SDL_RenderCopy(getRenderer(),decors.pSprite->pTexture,NULL,&(decors.pSprite->DstClip));
	renderSprite(tigre->pSprite);
	//rafraichissement du rendu dans la fenetre
	SDL_RenderPresent(getRenderer());

	mainEventLoop();
	//destruction de tout les sprites
	sprite_DestroyAll();
	//destruction du moteur de rendu
	SDL_DestroyRenderer(getRenderer());

	SDL_Quit();

	return 0;
}

int mainEventLoop()
{
	int end = 0;
	Foreground* tgr = getFg(0);
	tgr->bhv = standing;
	tgr->dir = E;
	unsigned char dirMask=0;
	SDL_Event evenement;
	printf("Starts main loop\n");
	while(!end)
	{
		SDL_PollEvent(&evenement);
		refreshPosition(dirMask);
		if(tgr->bhv == moving)
		{
			refreshAnimation(ANIM_FPS);
		}
		switch(evenement.type)
		{
			case SDL_KEYDOWN:
				switch(evenement.key.keysym.sym)
				{
					case SDLK_q:
						end=1;
					break;
					case SDLK_UP: dirMask 	 |= 8; break;
					case SDLK_DOWN: dirMask  |= 4; break;
					case SDLK_LEFT: dirMask  |= 2; break;
					case SDLK_RIGHT: dirMask |= 1; break;

				}
			break;
			case SDL_KEYUP:
				switch(evenement.key.keysym.sym)
				{
					case SDLK_r:
						printf("r released\n");
					break;
					case SDLK_UP: dirMask 	 &= 7 ; break;
					case SDLK_DOWN: dirMask  &= 11; break;
					case SDLK_LEFT: dirMask  &= 13; break;
					case SDLK_RIGHT: dirMask &= 14; break;
				}
			break;
			default:
			break;
		}
	}
return 0;
}
SDL_Rect winCentered(texture_info txi)
{
	return (SDL_Rect) {WIN_C_W-(txi.w/2),WIN_C_H-(txi.h/2),txi.w,txi.h};
}
void renderSprite(Sprite* sp)
{
	SDL_RenderCopy(getRenderer(),sp->pTexture,
		&(sp->SrcClip[sp->clipCount]),
		&(sp->DstClip));
	//printf("%zu\n",sp->clipCount);
	sp->clipCount = (sp->clipCount+1) % MAX_CLIP_COUNT;
}
void refreshAnimation(unsigned char fps)
{
	static unsigned int cTime, lTime;
	cTime = SDL_GetTicks();
	//printf("last time : %d\n current time : %d\n",lTime,cTime);
	if(cTime > (lTime + (1000/fps)))
	{
		Foreground* tgr = getFg(0);
		moveCharacter();

		renderSprite(tgr->pSprite);
		SDL_RenderPresent(getRenderer());
		lTime = cTime;
	}
}
void refreshPosition(unsigned char dirMask)
{
	enum direction dir;
	enum behaviour bhv;

	bhv=moving;
	switch(dirMask)
	{
		//orthos
		case 1: dir=E; break;
		case 2: dir=W; break;
		case 4: dir=S; break;
		case 8: dir=N; break;
		//diags
		case 5: dir=SE; break;
		case 6: dir=SW; break;
		case 9: dir=NE; break;
		case 10:dir=NW; break;

		default :
		bhv = standing;
		break;
	}
	getFg(0)->dir = dir;
	getFg(0)->bhv = bhv;
}
void moveCharacter()
{
	enum direction dir = getFg(0)->dir;
	SDL_Rect* pPos = &(getFg(0)->pSprite->DstClip);
	switch(dir)
	{
		case E:
			pPos->x++;
		break;
		case W:
			pPos->x--;
		break;
		case S:
			pPos->y++;
		break;
		case N:
			pPos->y--;
		break;
		case SE:
		break;
		case SW:
		break;
		case NE:
		break;
		case NW:
		break;
	}

	printf("x:%d y:%d\n"
	,getFg(0)->pSprite->DstClip.x 
	,getFg(0)->pSprite->DstClip.y);
}
