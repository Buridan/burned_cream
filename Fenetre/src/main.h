#include "window.h"
//#include "sprite.h"
#include "character.h"
enum behaviour{standing,moving,jumping};
enum direction{N,NE,E,SE,S,SW,W,NW};

typedef struct
{
	Sprite* pSprite;
}Background;

typedef struct
{
	Sprite* pSprite;
}Foreground;

int mainEventLoop();
SDL_Rect winCentered(texture_info txi);
void renderSprite(Sprite* sp);
void refreshAnimation();
void refreshPosition(enum direction dir);
