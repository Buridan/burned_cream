#include <SDL2/SDL.h>
#include "window.h"
/*
	@author : Busyvar
	@brief : goal of this lib is to make a texture for any kind of visual game element.
*/
#define MAX_CLIP_COUNT	8
#define MAX_SPRITE 3
typedef struct{Uint32 fmt;int acc,w,h;}texture_info;

typedef struct{
	size_t index;
	SDL_Texture* pTexture	;
	SDL_Rect	 SrcClip[MAX_CLIP_COUNT];
	size_t 		 clipCount;
	SDL_Rect	 DstClip	;
	texture_info Info		;
}Sprite;

//public
//constructeur
Sprite*		 sprite_Load(const char *pszSpritePath);
//destructeur
int			 sprite_DestroyAll();

//getters
Sprite* getSprite(size_t index);
Sprite* getLastSprite();
//private
Sprite 		 _sprite_Init(const char *pszSpritePath);
void		 _destroySprite(Sprite* pSprite);
SDL_Surface* _loadSurface(const char *pszSpritePath);
SDL_Texture* _loadTexture(SDL_Surface *pSurface);
void 		 _loadTextureInfo(texture_info* pInfo, SDL_Texture* pTexture);

