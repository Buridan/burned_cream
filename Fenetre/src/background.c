#include <stdlib.h>
#include "background.h"
#include <assert.h>

static Background m_bgList[MAX_BG];
static int m_bgIndex = -1;
Background* background_Load(const char* pszFilePath)
{
	Background bg;
	m_bgIndex++;
	printf("new background: %d/%d\n",m_bgIndex+1,MAX_BG);
	if(m_bgIndex >= MAX_BG)
	{
		printf("Error : Too much background loaded.\n");
	}
	bg.sprite = sprite_Load(pszFilePath);
	bg.srcRect = (SDL_Rect){0,0,bg.sprite.info.w, bg.sprite.info.h};
	bg.dstRect = (SDL_Rect){0,0,bg.sprite.info.w, bg.sprite.info.h};
	m_bgList[m_bgIndex] = bg;
	return &(m_bgList[m_bgIndex]);
}
void background_DestroyAll()
{
	while(m_bgIndex>=0)
	{
		sprite_Destroy(&(m_bgList[m_bgIndex].sprite));
		//assert(NULL == &(m_bgList[m_bgIndex].sprite);
		m_bgIndex--;
	}
}
void background_Destroy(Background* pBg)
{
	//assert(m_bgIndex > 0);
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
void background_copyAllToRender()
{
	for(int i=m_bgIndex;i>=0;i--)
	{
		background_copyToRender(&m_bgList[i]);
	}
}
void background_copyToRender(Background* pBg)
{
	if(SDL_RenderCopy(getRenderer(),pBg->sprite.pTexture,
		&(pBg->srcRect),
		&(pBg->dstRect)))
		fprintf(stderr,"Echec de copie : %s\n",SDL_GetError());
}
