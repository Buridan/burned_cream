#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "window.h"
#include "sprite.h"

int mainEventLoop();
SDL_Rect winCentered(texture_info txi);
void renderSprite(Sprite sp);
int main(int argc, char** argv)
{
	window_initAll();
	Sprite tigre  = loadSprite("./data/spritesheet.bmp");
	Sprite decors = loadSprite("./data/decors.bmp");

	//recuperation des dimensions de la texture
	//texture_info BGInfo={0,0,0,0};

	//SDL_QueryTexture(pTexture, &BGInfo.fmt, &BGInfo.acc, &BGInfo.w, &BGInfo.h);
	//source du sprite
	*tigre.pSrcClip = (SDL_Rect){0,15,tigre.pInfo->w/2,48};

	//destination du sprite
	*decors.pDstClip = winCentered(*decors.pInfo);
	*tigre.pDstClip = winCentered(*tigre.pInfo);

	//Copie de la texture dans le rendu
	SDL_RenderCopy(getRenderer(),decors.pTexture,NULL,decors.pDstClip);
	SDL_RenderCopy(getRenderer(),tigre.pTexture,tigre.pSrcClip,tigre.pDstClip);
	//rafraichissement du rendu dans la fenetre
	SDL_RenderPresent(getRenderer());

	mainEventLoop();
	//destruction de la texture
	destroySprite(&tigre);
	destroySprite(&decors);
	//destruction du moteur de rendu
	SDL_DestroyRenderer(getRenderer());

	SDL_Quit();

	return 0;
}

int mainEventLoop()
{
	int end = 0;
	SDL_Event evenement;
	while(!end)
	{
		SDL_WaitEvent(&evenement);
		switch(evenement.type)
		{
			case SDL_KEYDOWN:
			switch(evenement.key.keysym.sym)
			{
				case SDLK_q:
				end=1;
				SDL_RenderPresent(getRenderer());
				break;
			}
			break;
		}
	}
return 0;
}
SDL_Rect winCentered(texture_info txi)
{
	return (SDL_Rect) {WIN_C_W-(txi.w/2),WIN_C_H-(txi.h/2),txi.w,txi.h};
}
void renderSprite(Sprite sp)
{
	SDL_RenderCopy(getRenderer(),sp.pTexture,sp.pSrcClip,sp.pDstClip);
}
