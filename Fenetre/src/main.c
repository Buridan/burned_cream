#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "main.h"

int main(int argc, char** argv)
{
	window_initAll();
	Character* tigre = foreground_Load("./data/spritesheet.bmp");
	Background* decors = background_Load("./data/decors.bmp");

	//recuperation des dimensions de la texture
	//texture_info BGInfo={0,0,0,0};

	//SDL_QueryTexture(pTexture, &BGInfo.fmt, &BGInfo.acc, &BGInfo.w, &BGInfo.h);
	//source du sprite
	for(size_t i=0;i<MAX_CLIP_COUNT;i++)
	{
		tigre->fg.SrcClip[i] = (SDL_Rect){128 * i,15,tigre->fg.sprite.info.w/8,48};
	}

	//destination de depart du sprite
	decors->fg.dstRect = winCentered(decors->fg.sprite.info);
	tigre->fg.dstRect  = (SDL_Rect){0,0,128,48};

	//Copie de la texture dans le rendu
	renderBackground(decors);
	renderSprite(tigre->fg.sprite);
	//renderSprite(decors.pSprite);
	//rafraichissement du rendu dans la fenetre
	SDL_RenderPresent(getRenderer());

	mainEventLoop();
	//destruction de tout les sprites
	sprite_DestroyAll();
	//destruction du moteur de rendu
	SDL_DestroyRenderer(getRenderer());

	SDL_Quit();

	return 0;
}

int mainEventLoop()
{
	int end = 0;
	Foreground* tgr = getCh(1);
	tgr->bhv = standing;
	tgr->dir = E;
	unsigned char dirMask=0;
	SDL_Event evenement;
	printf("Starts main loop\n");
	while(!end)
	{
		SDL_PollEvent(&evenement);
		setDirection(dirMask);
		if(tgr->bhv == moving)
		{
			refreshAnimation(ANIM_FPS);
		}
		switch(evenement.type)
		{
			case SDL_KEYDOWN:
				switch(evenement.key.keysym.sym)
				{
					case SDLK_q:
						end=1;
					break;
					case SDLK_UP: dirMask 	 |= 8; break;
					case SDLK_DOWN: dirMask  |= 4; break;
					case SDLK_LEFT: dirMask  |= 2; break;
					case SDLK_RIGHT: dirMask |= 1; break;

				}
			break;
			case SDL_KEYUP:
				switch(evenement.key.keysym.sym)
				{
					case SDLK_r:
						printf("r released\n");
					break;
					case SDLK_UP: dirMask 	 &= 7 ; break;
					case SDLK_DOWN: dirMask  &= 11; break;
					case SDLK_LEFT: dirMask  &= 13; break;
					case SDLK_RIGHT: dirMask &= 14; break;
				}
			break;
			default:
			break;
		}
	}
return 0;
}
SDL_Rect winCentered(texture_info txi)
{
	return (SDL_Rect) {WIN_C_W-(txi.w/2),WIN_C_H-(txi.h/2),txi.w,txi.h};
}
void renderForeground(Foreground* fg)
{
	fg->srcRect = (fg->srcClip[fg->clipCount]);
	if(SDL_RenderCopy(getRenderer(),fg->sprite.pTexture,
		&(fg->srcRect),
		&(fg->dstRect)))
		fprintf(stderr,"Echec de copie : %s\n",SDL_GetError());
	//printf("%zu\n",sp->clipCount);
	fg->clipCount = (fg->clipCount+1) % MAX_CLIP_COUNT;
}
void renderBackground(Background* bg)
{
	if(SDL_RenderCopy(getRenderer(),bg->sprite.pTexture,
		&(bg->srcRect),
		&(bg->dstRect)))
		fprintf(stderr,"Echec de copie : %s\n",SDL_GetError());
}
void refreshAnimation(unsigned char fps)
{
	static unsigned int cTime, lTime;
	cTime = SDL_GetTicks();
	//printf("last time : %d\n current time : %d\n",lTime,cTime);
	if(cTime > (lTime + (1000/fps)))
	{
		Character* pTgr = getCh(1);
		Background* pBg = getBg(1);
		moveCharacter();

		renderBackground(pBg);
		renderForeground(&(pTgr->fg));
		//renderSprite(pTgr->fg.sprite);
		SDL_RenderPresent(getRenderer());
		lTime = cTime;
	}
}
void setDirection(const byte_t dirMask)
{
	enum direction dir;
	enum behaviour bhv;

	bhv=moving;
	switch(dirMask) //UP,DOWN,LEFT,RIGHT -> 0bUDLR
	{
		//orthos
		case 8: dir=N; break;
		case 4: dir=S; break;
		case 2: dir=W; break;
		case 1: dir=E; break;
		//diags
		case 5: dir=SE; break;
		case 6: dir=SW; break;
		case 9: dir=NE; break;
		case 10: dir=NW; break;

		default :
		bhv = standing;
		break;
	}
	getCh(1)->dir = dir; //!! nous ne savons pas à quel perso cette direction doit s'appliquer
	getCh(1)->bhv = bhv;
}
void moveCharacter()
{
	const float qPi = 0.7853; //un pas diagonal vaut un quart de pi sur x et y
	const int pas = 10; //10 pixels par pas sinon les diagonales seraient carrés
	const int pasDiag = qPi * pas;
	enum direction dir = getCh(1)->dir;
	SDL_Rect* pPos = &(getCh(1)->fg.dstRect);
	switch(dir)
	{
		case E: pPos->x+=pas; break;
		case W: pPos->x-=pas; break;
		case S: pPos->y+=pas; break;
		case N: pPos->y-=pas; break;
		case SE:
		pPos->x += pasDiag;
		pPos->y += pasDiag;
		break;
		case SW:
		pPos->x -= pasDiag;
		pPos->y += pasDiag;
		break;
		case NE:
		pPos->x += pasDiag;
		pPos->y -= pasDiag;
		break;
		case NW:
		pPos->x -= pasDiag;
		pPos->y -= pasDiag;
		break;
	}
	//printf("x:%d y:%d\n",pPos->x,pPos->y); 
}
