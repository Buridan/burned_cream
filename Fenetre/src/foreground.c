#include <stdlib.h>
#include <assert.h>
#include "foreground.h"

Foreground foreground_Load(const char* pszFilePath)
{
	Foreground foreground;
	foreground.sprite = sprite_Load(pszFilePath);
	foreground.dir = E;
	foreground.bhv = standing;
	foreground.clipCount = 0;
	return foreground;
}
