#include "sprite.h"
#define MAX_FG (MAX_SPRITE - 1)
#define MAX_CLIP_COUNT	8
#define ANIM_FPS	8

typedef struct
{
	Sprite 		 sprite;
	byte_t 		 srcRect;
	byte_t 		 clipCount;
	SDL_Rect	 srcClip[MAX_CLIP_COUNT];
	SDL_Rect	 dstRect;
}Foreground;

Foreground foreground_Load(const char* pszFilePath);
