#include <stdlib.h>
#include "init.h"
#include <assert.h>

static SDL_Window* 		m_pWindow 	= NULL;
static SDL_Renderer* 	m_pRenderer = NULL;

void initAll()
{
	_initSDL();
	_initWindow();
	_initRenderer();
}
/* initialisation de la SDL, de la fenêtre et du moteur de rendu */
int _initSDL()
{
	/* Initialisation simple */
	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
		return -1;
	}
	return 0;
}
/* Création de la fenêtre */
int _initWindow()
{
	m_pWindow = SDL_CreateWindow("titre de la fenêtre",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if(!m_pWindow )
	{
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
		return -1;
	}
	return 0;
}
//création du moteur de rendu
int _initRenderer()
{
	m_pRenderer = SDL_CreateRenderer(m_pWindow,-1,
							  SDL_RENDERER_ACCELERATED);
	if(!m_pRenderer )
	{
		fprintf(stderr,"Erreur de création du moteur de rendu: %s\n",SDL_GetError());
		return -1;
	}
	return 0;
}
SDL_Renderer* getRenderer()
{
	//return SDL_GetRenderer(m_pWindow);
	return m_pRenderer;
}
