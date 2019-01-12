#include <SDL2/SDL.h>
#include "window.h"
/*
	@author : Busyvar
	@brief : goal of this lib is to make a texture for any kind of visual game element.
*/
#define MAX_SPRITE 4
typedef struct{Uint32 fmt;int acc,w,h;}texture_info;
typedef struct{
	SDL_Texture* pTexture	;
	texture_info info	;
}Sprite;

//public
//constructeur
Sprite		 sprite_Load(const char *pszSpritePath);
//destructeur
void sprite_Destroy(Sprite* pSprite);
int sprite_DestroyAll();
//private
SDL_Surface* _loadSurface(const char *pszSpritePath);
SDL_Texture* _loadTexture(SDL_Surface* pSurface);
texture_info _loadTextureInfo(SDL_Texture* pTexture);

