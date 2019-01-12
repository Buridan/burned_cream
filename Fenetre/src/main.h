//#include "window.h"
//#include "background.h"
#include "character.h"

int mainEventLoop();
void renderBackground(Background* bg);
void refreshAnimation(unsigned char fps);
void setDirection(const byte_t dirMask);
void moveCharacter();
