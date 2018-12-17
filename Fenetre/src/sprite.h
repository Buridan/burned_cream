#include <SDL2/SDL.h>
/*
	@author : Busyvar
	@brief : goal of this lib is to make a texture for any kind of visual game element.
*/
//TODO : utiliser sprite.c pour charger indifferemment le decors des autres images
//public
void initSprite();
SDL_Texture* getTexSprite();

//private
void _loadTexture();
void _loadSprite();
