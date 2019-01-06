#include "sprite.h"
#define MAX_BG 1

typedef struct
{
	Sprite 		 sprite;
	SDL_Rect 	 srcRect;
	SDL_Rect	 dstRect;
}Background;

Background* background_Load(const char* pszFilePath);

void background_DestroyAll();
void background_Destroy(Background* pBg);
Background* getBg(byte_t b);
