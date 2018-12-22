#include <stdlib.h>
#include <assert.h>
#include "sprite.h"

static SDL_Surface* m_pSprite 		= NULL;
static SDL_Texture* m_pTexSprite 	= NULL;
//static SDL_Rect		m_srcClip		= NULL;
//static SDL_Rect		m_dstClip		= NULL;
static texture_info m_pTexInfo		= {0,0,0,0};

int loadSprite(char *pszSpritePath)
{
	m_pSprite = SDL_LoadBMP(pszSpritePath);
	if(!m_pSprite)
	{
		fprintf(stderr,"Echec de chargement du sprite : %s",SDL_GetError());
		return -1;
	}
	assert(m_pSprite);
	_loadTexture();
	SDL_FreeSurface(m_pSprite);
	return 0;
}
//permet de récupérer la hauteur et la largeur de l'image notamment
texture_info getSpriteTextureInfo()
{
	assert(m_pTexInfo.w && m_pTexInfo.h);
	return m_pTexInfo;
}
SDL_Texture* getSpriteTexture()
{
	return m_pTexSprite;
}
void _loadTexture()
{
	m_pTexSprite = SDL_CreateTextureFromSurface(getRenderer(),m_pSprite);
	if(!m_pTexSprite)
		fprintf(stderr,"Echec de chargement de la texture : %s",SDL_GetError());
	assert(m_pTexSprite);
	_setTextureInfo();
}
void _setTextureInfo()
{
	SDL_QueryTexture(m_pTexSprite,
		&m_pTexInfo.fmt,
		&m_pTexInfo.acc,
		&m_pTexInfo.w,
		&m_pTexInfo.h);
}
