#include <stdlib.h>
#include <assert.h>
#include "sprite.h"
#include "init.h"

static SDL_Surface* m_pSprite 		= NULL;
static char* 		m_spritePath 	= "./data/spritesheet.bmp";
static SDL_Texture* m_pTexSprite 	= NULL;

void initSprite()
{
	_loadSprite();
	_loadTexture();
	SDL_FreeSurface(m_pSprite);
}
void _loadSprite()
{
	m_pSprite = SDL_LoadBMP(m_spritePath);
	if(!m_pSprite)
		fprintf(stderr,"Echec de chargement du sprite : %s",SDL_GetError());
	assert(m_pSprite);
}
void _loadTexture()
{
	m_pTexSprite = SDL_CreateTextureFromSurface(getRenderer(),m_pSprite);
	if(!m_pTexSprite)
		fprintf(stderr,"Echec de chargement de la texture : %s",SDL_GetError());
	assert(m_pTexSprite);
}
SDL_Texture* getTexSprite()
{
	return m_pTexSprite;
}
