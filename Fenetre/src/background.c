#include <stdlib.h>
#include "background.h"
#include <assert.h>

static Background m_bgList[MAX_BG];
static byte_t m_bgLoaded = 0;
Background* background_Load(const char* pszFilePath)
{
	Background bg;
	m_bgLoaded++;
	if(m_bgLoaded >= MAX_BG)
	{
		printf("Error : Too much background loaded.\n");
	}
	bg.sprite = sprite_Load(pszFilePath);
	bg.srcRect = (SDL_Rect){0,0,bg.sprite.info.w, bg.sprite.info.h};
	bg.dstRect = (SDL_Rect){0,0,bg.sprite.info.w, bg.sprite.info.h};
	m_bgList[m_bgLoaded] = bg;
	return &(m_bgList[m_bgLoaded]);
}
void background_DestroyAll()
{
	while(m_bgLoaded>0)
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
