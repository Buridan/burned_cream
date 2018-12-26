#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "main.h"

int main(int argc, char** argv)
{
	window_initAll();
	Sprite* tigre  = sprite_Load("./data/spritesheet.bmp");
	Sprite* decors = sprite_Load("./data/decors.bmp");

	//recuperation des dimensions de la texture
	//texture_info BGInfo={0,0,0,0};

	//SDL_QueryTexture(pTexture, &BGInfo.fmt, &BGInfo.acc, &BGInfo.w, &BGInfo.h);
	//source du sprite
	for(size_t i=0;i<MAX_CLIP_COUNT;i++)
	{
		tigre->SrcClip[i] = (SDL_Rect){128 * i,15,tigre->pInfo->w/6,48};
	}

	//destination du sprite
	decors->DstClip = winCentered(*decors->pInfo);
	tigre->DstClip  = (SDL_Rect){0,0,64,48};

	//Copie de la texture dans le rendu
	SDL_RenderCopy(getRenderer(),decors->pTexture,NULL,&(decors->DstClip));
	renderSprite(tigre);
	//SDL_RenderCopy(getRenderer(),tigre.pTexture,tigre.pSrcClip[0],tigre.pDstClip);
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
	enum behaviour bhv = standing;
	SDL_Event evenement;
	printf("Starts main loop\n");
	while(!end)
	{
		SDL_PollEvent(&evenement);
		if(bhv == moving)
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
					case SDLK_DOWN:
					case SDLK_LEFT:
					case SDLK_RIGHT:
						bhv=moving;
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
					case SDLK_DOWN:
					case SDLK_LEFT:
					case SDLK_RIGHT:
						bhv=standing;
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
		Sprite* tgr = getSprite(0);
		renderSprite(tgr);
		SDL_RenderPresent(getRenderer());
		lTime = cTime;
	}
}
void refreshPosition(enum direction dir)
{
	
}
