#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include "data/decors.h"

#define WIN_W	640
#define WIN_H	480
#define WIN_C_W WIN_W/2
#define WIN_C_H	WIN_H/2

typedef struct {Uint32 fmt;int acc,w,h;}texture_info;
SDL_Rect targetZoneCentered(texture_info txi);

int main(int argc, char** argv)
{

	/* Initialisation simple */
	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
		return -1;
	}
	{
		SDL_Window* pWindow = NULL;
		SDL_Event evenement;
		int end = 0;

		/* Création de la fenêtre */
		pWindow = SDL_CreateWindow("Ma première application SDL2",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIN_W, WIN_H, SDL_WINDOW_SHOWN);

		if(!pWindow )
			fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
		//creation du moteur de rendu pour la fenetre
		SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow,-1,
								  SDL_RENDERER_ACCELERATED);
		//l'image se charge depuis la memoire
		SDL_RWops *raw = SDL_RWFromMem(MagickImage ,sizeof(MagickImage));
		SDL_Surface* pDecors = IMG_Load_RW(raw,1);
		if(NULL==pDecors) printf("Error : %s\n",SDL_GetError());

		IMG_Init(IMG_INIT_JPG);
		//SDL_Surface* pDecors = SDL_LoadBMP("./data/decors.bmp");
		IMG_Quit();
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pDecors);
		assert(pTexture && pDecors && pRenderer);
		//liberation des données de la surface
		SDL_FreeSurface(pDecors);
		//recuperation des dimensions de la texture
		texture_info txInfo={0,0,0,0};
		SDL_QueryTexture(pTexture,&txInfo.fmt,&txInfo.acc,&txInfo.w,&txInfo.h);

		//destination du sprite
		SDL_Rect dest =	targetZoneCentered(txInfo);	//Copie de la texture dans le rendu
		SDL_RenderCopy(pRenderer,pTexture,NULL,&dest);
		//rafraichissement du rendu dans la fenetre
		SDL_RenderPresent(pRenderer);
		//boucle principale
		while(!end)
		{
			SDL_WaitEvent(&evenement);
			switch(evenement.type)
			{
				case SDL_QUIT:
				case SDL_KEYDOWN:
					end = 1;
					break;
			}
		}
		//destruction de la texture
		SDL_DestroyTexture(pTexture);
		//destruction du moteur de rendu
		SDL_DestroyRenderer(pRenderer);
	}

	SDL_Quit();

	return 0;
}
SDL_Rect targetZoneCentered(texture_info txi)
{
	SDL_Rect result = {WIN_C_W-(txi.w/2),WIN_C_H-(txi.h/2),txi.w,txi.h};
	return result;
}

