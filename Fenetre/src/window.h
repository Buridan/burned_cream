#include <SDL2/SDL.h>
#define WIN_W	640
#define WIN_H	480
#define WIN_C_W WIN_W/2
#define WIN_C_H	WIN_H/2

void window_initAll();
int _initSDL();
int _initWindow();
int _initRenderer();
SDL_Renderer* getRenderer();

