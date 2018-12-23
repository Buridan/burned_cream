#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "window.h"
#include "sprite.h"

int mainEventLoop();
SDL_Rect winCentered(texture_info txi);
int main(int argc, char** argv)
{
	window_initAll();
	//chargement à l'exécution de l'image du sprite
	SDL_Surface* pDecors = SDL_LoadBMP("./data/decors.bmp");
	assert(pDecors);
	SDL_Texture* pTexture =   SDL_CreateTextureFromSurface(getRenderer(),pDecors);
	assert(pTexture);
	//liberation des données de la surface
	SDL_FreeSurface(pDecors);
	//charge le sprite du perso
	//initSprite();
	Sprite tigre = loadSprite("./data/spritesheet.bmp");

	//recuperation des dimensions de la texture
	texture_info BGInfo={0,0,0,0};
	texture_info* pFrame=tigre.pInfo;

	SDL_QueryTexture(pTexture, &BGInfo.fmt, &BGInfo.acc, &BGInfo.w, &BGInfo.h);
	//SDL_QueryTexture(getSpriteTexture(), &frame.fmt, &frame.acc, &frame.w, &frame.h);
	//rectangle source du sprite
	SDL_Rect SPClip = {0,15,pFrame->w/2,48};

	//destination du sprite
	SDL_Rect BGdest = winCentered(BGInfo);
	SDL_Rect SPdest = winCentered(*pFrame);

	//Copie de la texture dans le rendu
	SDL_RenderCopy(getRenderer(),pTexture,NULL,&BGdest);
	SDL_RenderCopy(getRenderer(),tigre.pTexture,&SPClip,&SPdest);
	//rafraichissement du rendu dans la fenetre
	SDL_RenderPresent(getRenderer());

	mainEventLoop();
	//destruction de la texture
	SDL_DestroyTexture(pTexture);
	destroySprite(&tigre);
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
				end=1;
				SDL_RenderPresent(getRenderer());
				break;
		}
	}
return 0;
}
SDL_Rect winCentered(texture_info txi)
{
	return (SDL_Rect) {WIN_C_W-(txi.w/2),WIN_C_H-(txi.h/2),txi.w,txi.h};
}
