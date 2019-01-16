#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "main.h"

int main(int argc, char** argv)
{
	window_initAll();
	Character* tigre = character_Init("./data/spritesheet.bmp");
	Character* trump = character_Init("./data/spritesheet2.bmp");
	Background* decors = background_Load("./data/decors.bmp");

	//recuperation des dimensions de la texture
	//texture_info BGInfo={0,0,0,0};

	//source du sprite

	//destination de depart du sprite
	decors->dstRect = background_setCentered(decors);
	tigre->fg.dstRect  = (SDL_Rect){0,0,64,24};
	trump->fg.dstRect  = (SDL_Rect){100,100,128,128};

	//Copie de la texture dans le rendu
	background_copyAllToRender();
	character_copyAllToRender();
	//rafraichissement du rendu dans la fenetre
	SDL_RenderPresent(getRenderer());

	mainEventLoop();
	//destruction de tout les assets
	character_DestroyAll();
	background_DestroyAll();
	//destruction du moteur de rendu
	SDL_DestroyRenderer(getRenderer());

	SDL_Quit();

	return 0;
}

int mainEventLoop()
{
	int end = 0;
	Character* tgr = getCh(0);
	byte_t dirMask=0;
	SDL_Event evenement;
	printf("Starts main loop\n");
	while(!end)
	{
		SDL_PollEvent(&evenement);
		character_setDirection(getCh(0),dirMask);
		if(tgr->bhv == moving)
		{
			refreshAnimation(ANIM_FPS);
			refreshMove(MOVE_FPS);
		}
		switch(evenement.type)
		{
			case SDL_KEYDOWN:
				switch(evenement.key.keysym.sym)
				{
					case SDLK_q:
						end=1;
					break;
					case SDLK_k: case SDLK_UP: dirMask 	 |= 8; break;
					case SDLK_j: case SDLK_DOWN: dirMask  |= 4; break;
					case SDLK_h: case SDLK_LEFT: dirMask  |= 2; break;
					case SDLK_l: case SDLK_RIGHT: dirMask |= 1; break;

				}
			break;
			case SDL_KEYUP:
				switch(evenement.key.keysym.sym)
				{
					case SDLK_r:
						printf("r released\n");
					break;
					case SDLK_k: case SDLK_UP: dirMask 	 &= 7 ; break;
					case SDLK_j: case SDLK_DOWN: dirMask  &= 11; break;
					case SDLK_h: case SDLK_LEFT: dirMask  &= 13; break;
					case SDLK_l: case SDLK_RIGHT: dirMask &= 14; break;
				}
			break;
			default:
			break;
		}
	}
return 0;
}

void refreshAnimation(const byte_t fps)
{
	static unsigned int cTime, lTime;
	cTime = SDL_GetTicks();
	//printf("last time : %d\n current time : %d\n",lTime,cTime);
	if(cTime > (lTime + (1000/fps)))
	{
		background_copyAllToRender();
		character_nextImage(getCh(0));
		character_copyAllToRender();
		SDL_RenderPresent(getRenderer());
		lTime = cTime;
	}
}
void refreshMove(const byte_t fps) //pourquoi recopier l'intégralité des sprites si certains n'ont pas bougé?
{
	static unsigned int cTime, lTime;
	cTime = SDL_GetTicks();
	//printf("last time : %d\n current time : %d\n",lTime,cTime);
	if(cTime > (lTime + (1000/fps)))
	{
		Character* pTgr = getCh(0);
		character_move(pTgr);
		background_copyAllToRender();
		character_copyAllToRender();
		SDL_RenderPresent(getRenderer());
		lTime = cTime;
	}
}
