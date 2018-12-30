#include "sprite.h"
#define MAX_FG (MAX_SPRITE - 1)
#define ANIM_FPS	8
enum behaviour{standing,moving,jumping};
enum direction{N,NE,E,SE,S,SW,W,NW};

typedef struct
{
	Sprite* pSprite;
	enum direction dir;
	enum behaviour bhv;
}Foreground;

Foreground* foreground_Load(const char* pszFilePath);
Foreground* getFg(const size_t index);
