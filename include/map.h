#pragma once 


#include "physics.h"
#include "window.h"

#define BACKGROUND_WIDTH 2304
#define BACKGROUND_HEIGHT 1296

#define GROUND_WIDTH BACKGROUND_WIDTH
#define GROUND_HEIGHT (WINDOW_HEIGHT / 4)

typedef struct {
    StaticBody_t ground ;
    SDL_Texture * background ;
} Map_t ;


Map_t * map_constructor () ;
void map_destructor (Map_t ** map) ;