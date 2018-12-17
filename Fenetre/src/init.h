#include <SDL2/SDL.h>
#define WIN_W	640
#define WIN_H	480
#define WIN_C_W WIN_W/2
#define WIN_C_H	WIN_H/2

void initAll();
int _initSDL();
int _initWindow();
int _initRenderer();
SDL_Renderer* getRenderer();

typedef struct{Uint32 fmt;int acc,w,h;}texture_info;
