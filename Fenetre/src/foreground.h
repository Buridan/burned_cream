#include "sprite.h"
#define MAX_FG (MAX_SPRITE - 1)
typedef struct
{
	Sprite* pSprite;
}Foreground;

Foreground* foreground_Load(const char* pszFilePath);
Foreground* getFg(const size_t index);
