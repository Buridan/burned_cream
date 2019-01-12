#include "background.h"
#define MAX_FG (MAX_SPRITE - MAX_BG)
#define MAX_CLIP_COUNT	8
#define ANIM_FPS	8

typedef struct
{
	Sprite 		 sprite;
	SDL_Rect 	 srcRect;
	SDL_Rect	 dstRect;
	byte_t 		 clipCount;
	SDL_Rect	 srcClip[MAX_CLIP_COUNT];
}Foreground;

Foreground foreground_Load(const char* pszFilePath);
void foreground_copyToRender(Foreground* fg);
