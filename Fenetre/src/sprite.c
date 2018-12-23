#include <stdlib.h>
#include <assert.h>
#include "sprite.h"

Sprite loadSprite(const char *pszSpritePath)
{
	Sprite sprite;
	//sprite.pTexture = NULL;
	sprite.pSrcClip	= malloc(sizeof(SDL_Rect));
	sprite.pDstClip	= malloc(sizeof(SDL_Rect));
	sprite.pInfo	= malloc(sizeof(texture_info));
	
	SDL_Surface* pSurface = _loadSurface(pszSpritePath);
	sprite.pTexture = _loadTexture(pSurface);
	_loadTextureInfo( (texture_info*) sprite.pInfo, (SDL_Texture*) sprite.pTexture);
	SDL_FreeSurface(pSurface);
	return sprite;
}
int	destroySprite(Sprite* pSprite)
{
	SDL_DestroyTexture(pSprite->pTexture);
	free(pSprite->pInfo);
	return 0;
}
//permet de récupérer la hauteur et la largeur de l'image notamment
//texture_pInfo getSpriteTextureInfo(texture_pInfo* pTxi)
//{
//	assert(pTxi->w && pTxi->h);
//	return pTxi;
//}
//SDL_Texture* getSpriteTexture(SDL_Texture* pTexture) //deprecated
//{
//	return pTexture;
//}

SDL_Surface* _loadSurface(const char *pszSpritePath)
{
	SDL_Surface* pSurface = SDL_LoadBMP(pszSpritePath);

	if(!pSurface)
	{
		fprintf(stderr,"Echec de chargement du sprite : %s",SDL_GetError());
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
void _loadTextureInfo(texture_info* pInfo, SDL_Texture* pTexture)
{
	SDL_QueryTexture(pTexture,
		&(pInfo->fmt),
		&(pInfo->acc),
		&(pInfo->w),
		&(pInfo->h));
	assert(pInfo->w && pInfo->h);
}
