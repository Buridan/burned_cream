#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>

#define WIN_W	640
#define WIN_H	480
#define WIN_C_W 	WIN_W/2
#define WIN_C_H	WIN_H/2

int main(int argc, char** argv)
{
	/* Initialisation simple */
	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
		return -1;
	}
	{
		/* Création de la fenêtre */
		SDL_Window* pWindow = NULL;
		pWindow = SDL_CreateWindow("Ma première application SDL2",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIN_W, WIN_H, SDL_WINDOW_SHOWN);

		if(!pWindow )
			fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
		//creation du moteur de rendu pour la fenetre
		SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow,-1,
								  SDL_RENDERER_ACCELERATED);
		//chargement de l'image du sprite
		SDL_Surface* pSprite = SDL_LoadBMP("./data/decors.bmp");
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite);
		assert(pTexture && pSprite && pRenderer);
		SDL_FreeSurface(pSprite);//plus utile ensuite
		//recuperation des dimensions de la texture
		struct {Uint32 fmt;int acc,w,h;}txInfo={NULL,NULL,0,0};
		SDL_QueryTexture(pTexture,&txInfo.fmt,&txInfo.acc,&txInfo.w,&txInfo.h);

		//destination du sprite
		SDL_Rect dest ={WIN_C_W-(txInfo.w/2),WIN_C_H-(txInfo.h/2),txInfo.w,txInfo.h};
		//Copie de la texture sur l'ecran
		SDL_RenderCopy(pRenderer,pTexture,NULL,&dest);
		//rafraichissement du rendu de l'ecran
		SDL_RenderPresent(pRenderer);
		//attente
		SDL_Delay(3000);
		//destruction de la texture
		SDL_DestroyTexture(pTexture);
		//destruction du moteur de rendu
		SDL_DestroyRenderer(pRenderer);
	}

	SDL_Quit();

	return 0;
}
