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
	unsigned char dirMask;
	SDL_Event evenement;
	printf("Starts main loop\n");
	while(!end)
	{
		SDL_PollEvent(&evenement);
		if(tgr->bhv == moving)
			refreshAnimation();
		switch(evenement.type)
		{
			case SDL_KEYDOWN:
				switch(evenement.key.keysym.sym)
				{
					case SDLK_q:
						end=1;
					break;
					case SDLK_UP:
						dirMask |= 8;
					case SDLK_DOWN:
						dirMask |= 4;
					case SDLK_LEFT:
						dirMask |= 2;
					case SDLK_RIGHT:
						dirMask |= 1;
						tgr->bhv=moving;
					break;

				}
			break;
			case SDL_KEYUP:
				switch(evenement.key.keysym.sym)
				{
					case SDLK_r:
					printf("r released\n");
					break;
					case SDLK_UP:
						dirMask &= 7;
					case SDLK_DOWN:
						dirMask &= 11;
					case SDLK_LEFT:
						dirMask &= 13;
					case SDLK_RIGHT:
						dirMask &= 14;
						tgr->bhv=standing;
					break;
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
void refreshAnimation()
{
	static unsigned int cTime, lTime;
	cTime = SDL_GetTicks();
	//printf("last time : %d\n current time : %d\n",lTime,cTime);
	if(cTime > (lTime + 200))
	{
		Foreground* tgr = getFg(0);
		renderSprite(tgr->pSprite);
		SDL_RenderPresent(getRenderer());
		lTime = cTime;
	}
}
void refreshPosition(enum direction dir)
{
	
}
