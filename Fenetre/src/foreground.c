#include <stdlib.h>
#include <assert.h>
#include "foreground.h"

static void _setSourceClip(SDL_Rect* sc,int clW,int clH,int hOff,byte_t numOfClip,texture_info inf);
Foreground foreground_Load(const char* pszFilePath)
{
	Foreground foreground;
	foreground.sprite = sprite_Load(pszFilePath);
	foreground.clipCount = 0;
	_setSourceClip(foreground.srcClip, 128, 48, 15, 8,foreground.sprite.info);
	return foreground;
}
static void _setSourceClip(SDL_Rect* sc,int clW,int clH,int hOff,byte_t numOfClip,texture_info inf)
{
	for(byte_t i=0;i<MAX_CLIP_COUNT;i++)
	{
		sc[i] = (SDL_Rect){clW * i,hOff,inf.w/numOfClip,clH};
	}
}
