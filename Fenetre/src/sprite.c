#include <stdlib.h>
#include <assert.h>
#include "sprite.h"

Sprite sprite_Load(const char *pszSpritePath)
{
	Sprite sprite;
	
	SDL_Surface* pSurface = _loadSurface(pszSpritePath);
	sprite.pTexture = _loadTexture(pSurface);
	sprite.info = _loadTextureInfo(sprite.pTexture);
	SDL_FreeSurface(pSurface);
	return sprite;
}
void sprite_Destroy(Sprite* pSprite)
{
	printf("destroying sprite %ph\n",(void *) pSprite);
	SDL_DestroyTexture(pSprite->pTexture);
	pSprite = NULL;
}

SDL_Surface* _loadSurface(const char *pszSpritePath)
{
	SDL_Surface* pSurface = SDL_LoadBMP(pszSpritePath);

	if(!pSurface)
	{
		fprintf(stderr,"Echec de chargement du sprite : %s\n",SDL_GetError());
	}
	//assert(pSurface);
	return pSurface;
}
SDL_Texture* _loadTexture(SDL_Surface *pSurface)
{
	SDL_Texture* pTex = SDL_CreateTextureFromSurface(getRenderer(),pSurface);
	if(!pTex){
		fprintf(stderr,"Echec de chargement de la texture : %s",SDL_GetError());
	}
	return pTex;
}
texture_info _loadTextureInfo(SDL_Texture* pTexture)
{
	texture_info txi;
	SDL_QueryTexture(pTexture,
		&txi.fmt,
		&txi.acc,
		&txi.w,
		&txi.h);
	assert(txi.w && txi.h);
	return txi;
}
