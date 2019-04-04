#include <stdlib.h>
#include <assert.h>
#include "foreground.h"

static void _setSourceClip(SDL_Rect* sc,animation_grid gr,byte_t numOfClip,texture_info inf);
Foreground foreground_Load(const char* pszFilePath)
{
	Foreground foreground;
	foreground.sprite = sprite_Load(pszFilePath);
	foreground.clipCount = 0;
	foreground.clipMax = 8;
	foreground.aGrid = (animation_grid){(clip){0,15,128,48},0,7,0,0};
	_setSourceClip(foreground.srcClip, foreground.aGrid, foreground.clipMax,foreground.sprite.info);
	return foreground;
}
static void _setSourceClip(SDL_Rect* sc,animation_grid gr,byte_t numOfClip,texture_info inf)
{
	for(byte_t i=0;i<MAX_CLIP_COUNT;i++)
	{
		sc[i] = (SDL_Rect){gr.cl.w * i,gr.cl.y,inf.w/numOfClip,gr.cl.h};
	}
}
void foreground_copyToRender(Foreground* pFg)
{
	pFg->srcRect = (pFg->srcClip[pFg->clipCount]);
	if(SDL_RenderCopy(getRenderer(),pFg->sprite.pTexture,
		&(pFg->srcRect),
		&(pFg->dstRect)))
		fprintf(stderr,"Echec de copie : %s\n",SDL_GetError());
	//printf("%zu\n",sp->clipCount);
}
Foreground foreground_nextClip(Foreground fg)
{
	fg.clipCount = (fg.clipCount+1) % fg.clipMax;
	return fg;
}
