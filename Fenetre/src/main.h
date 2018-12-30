#include "window.h"
#include "foreground.h"
//#include "character.h"


typedef struct
{
	Sprite* pSprite;
}Background;

typedef struct
{
	Foreground* pFg;
//	enum direction dir;
//	enum behaviour bhv;
}Character;

int mainEventLoop();
SDL_Rect winCentered(texture_info txi);
void renderSprite(Sprite* sp);
void renderBackground(Sprite* bg);
void refreshAnimation(unsigned char fps);
void setDirection(unsigned char dirMask);
void moveCharacter();
