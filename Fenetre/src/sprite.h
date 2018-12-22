#include <SDL2/SDL.h>
#include "window.h"
/*
	@author : Busyvar
	@brief : goal of this lib is to make a texture for any kind of visual game element.
*/
//TODO : utiliser sprite.c pour charger indifferemment le decors des autres images
//public
typedef struct{Uint32 fmt;int acc,w,h;}texture_info;


int loadSprite(char *pszSpritePath);
SDL_Texture* getSpriteTexture();
texture_info getSpriteTextureInfo();

//private
void _loadTexture();
void _setTextureInfo();

