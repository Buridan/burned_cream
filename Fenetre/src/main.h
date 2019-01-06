#include "window.h"
#include "background.h"
#include "character.h"

int mainEventLoop();
SDL_Rect winCentered(texture_info txi);
void renderSprite(Sprite* sp);
void renderForeground(Foreground* fg);
void renderBackground(Background* bg);
void refreshAnimation(unsigned char fps);
void setDirection(const byte_t dirMask);
void moveCharacter();
