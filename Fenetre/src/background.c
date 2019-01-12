#include <stdlib.h>
#include "background.h"
#include <assert.h>

static Background m_bgList[MAX_BG];
static int m_bgLoaded = 0;
Background* background_Load(const char* pszFilePath)
{
	Background bg;
	printf("new background: %d/%d\n",m_bgLoaded+1,MAX_BG);
	if(m_bgLoaded >= MAX_BG)
	{
		printf("Error : Too much background loaded.\n");
	}
	bg.sprite = sprite_Load(pszFilePath);
	bg.srcRect = (SDL_Rect){0,0,bg.sprite.info.w, bg.sprite.info.h};
	bg.dstRect = (SDL_Rect){0,0,bg.sprite.info.w, bg.sprite.info.h};
	m_bgList[m_bgLoaded] = bg;
	m_bgLoaded++;
	return &(m_bgList[m_bgLoaded-1]);
}
void background_DestroyAll()
{
	m_bgLoaded--;
	while(m_bgLoaded>=0)
	{
		sprite_Destroy(&(m_bgList[m_bgLoaded].sprite));
		//assert(NULL == &(m_bgList[m_bgLoaded].sprite);
		m_bgLoaded--;
	}
}
void background_Destroy(Background* pBg)
{
	//assert(m_bgLoaded > 0);
	printf("destroying background %ph\n",(void*) pBg);
	sprite_Destroy(&(pBg->sprite));
	//assert(NULL == &(pBg->sprite));
	pBg = NULL;
}
Background* getBg(byte_t b)
{
	return &(m_bgList[b]);
}
SDL_Rect background_setCentered(Background* pBg)
{
	texture_info txi = pBg->sprite.info;
	return (SDL_Rect) {WIN_C_W-(txi.w/2),WIN_C_H-(txi.h/2),txi.w,txi.h};
}
