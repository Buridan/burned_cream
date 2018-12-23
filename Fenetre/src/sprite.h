#include <SDL2/SDL.h>
#include "window.h"
/*
	@author : Busyvar
	@brief : goal of this lib is to make a texture for any kind of visual game element.
*/
//TODO : utiliser sprite.c pour charger indifferemment le decors des autres images
//public
typedef struct{Uint32 fmt;int acc,w,h;}texture_info;

typedef struct{
	//char *pszSpritePath;
	//SDL_Surface* pSurface	;
	SDL_Texture* pTexture	;
	SDL_Rect	 srcClip	;
	SDL_Rect	 dstClip	;
	texture_info* pInfo		;
}Sprite;

//constructeur
Sprite		  loadSprite(const char *pszSpritePath);
//destructeur
int			  destroySprite(Sprite* pSprite);
//SDL_Texture* getSpriteTexture();
//texture_info getSpriteTextureInfo();

//private
SDL_Surface* _loadSurface(const char *pszSpritePath);
SDL_Texture* _loadTexture(SDL_Surface *pSurface);
void _loadTextureInfo(texture_info* pInfo, SDL_Texture* pTexture);

