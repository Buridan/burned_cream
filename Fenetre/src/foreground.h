#include "background.h"
#define MAX_FG (MAX_SPRITE - MAX_BG)
#define MAX_CLIP_COUNT	8
#define ANIM_FPS	12

typedef struct { int x,y,w,h; }clip;
typedef struct
{
	clip cl;
	uint8_t col,maxCol,line,maxLine;
}animation_grid; //used to describe how spritesheet zones are made
	
typedef struct
{
	Sprite 		 sprite;
	SDL_Rect 	 srcRect;
	SDL_Rect	 dstRect;
	animation_grid aGrid;
	byte_t 		 clipCount, clipMax;
	SDL_Rect	 srcClip[MAX_CLIP_COUNT];
}Foreground;

Foreground foreground_Load(const char* pszFilePath);
void foreground_copyToRender(Foreground* fg);
Foreground foreground_nextClip(Foreground fg);
