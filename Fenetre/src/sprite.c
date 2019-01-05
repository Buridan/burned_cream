#include <stdlib.h>
#include <assert.h>
#include "sprite.h"

static Sprite m_spriteList[MAX_SPRITE];
static byte_t m_spriteIndex=0;
Sprite* sprite_Load(const char *pszSpritePath)
{
	Sprite* pRes;
	if(m_spriteIndex >= MAX_SPRITE-1)
	{
		printf("Error : Too much sprite loaded\n");
	}
	m_spriteList[m_spriteIndex] = _sprite_Init(pszSpritePath);
	pRes = &(m_spriteList[m_spriteIndex]);
	m_spriteIndex++;
	return pRes;
}
Sprite _sprite_Init(const char *pszSpritePath)
{
	Sprite sprite;
	//sprite.pTexture = NULL;
	sprite.index = m_spriteIndex;
	sprite.clipCount = 0;
	//sprite.SrcClip[0]	= malloc(MAX_CLIP_COUNT * sizeof(SDL_Rect));
	//sprite.DstClip	= malloc(sizeof(SDL_Rect));
	//sprite.pInfo	= malloc(sizeof(texture_info));
	
	SDL_Surface* pSurface = _loadSurface(pszSpritePath);
	sprite.pTexture = _loadTexture(pSurface);
	_loadTextureInfo( &sprite.Info, (SDL_Texture*) sprite.pTexture);
	SDL_FreeSurface(pSurface);
	return sprite;
}
int sprite_DestroyAll()
{
	Sprite* pSpriteToDestroy;
	m_spriteIndex--;
	while(255!=m_spriteIndex) // 255 = byte underflow
	{
		printf("destroying sprite %d : %ph\n",m_spriteIndex,(void*) &m_spriteList[m_spriteIndex]);
		pSpriteToDestroy = &m_spriteList[m_spriteIndex];
		_destroySprite(pSpriteToDestroy);
		m_spriteIndex--;
	};
	return 0;
}
Sprite* getSprite(byte_t index)
{
	return &(m_spriteList[index]);
}
Sprite* getLastSprite()
{
	return &(m_spriteList[m_spriteIndex-1]);
}
void _destroySprite(Sprite* pSprite)
{
	SDL_DestroyTexture(pSprite->pTexture);
	//free(pSprite->pInfo);
	//free(pSprite->pSrcClip);
	//pSprite = NULL;
}

SDL_Surface* _loadSurface(const char *pszSpritePath)
{
	SDL_Surface* pSurface = SDL_LoadBMP(pszSpritePath);

	if(!pSurface)
	{
		fprintf(stderr,"Echec de chargement du sprite : %s\n",SDL_GetError());
	}
	//assert(pSurface);
	return pSurface;
}
SDL_Texture* _loadTexture(SDL_Surface *pSurface)
{
	SDL_Texture* pTex = SDL_CreateTextureFromSurface(getRenderer(),pSurface);
	if(!pTex){
		fprintf(stderr,"Echec de chargement de la texture : %s",SDL_GetError());
	}
	return pTex;
}
void _loadTextureInfo(texture_info* pInfo, SDL_Texture* pTexture)
{
	SDL_QueryTexture(pTexture,
		&(pInfo->fmt),
		&(pInfo->acc),
		&(pInfo->w),
		&(pInfo->h));
	assert(pInfo->w && pInfo->h);
}
