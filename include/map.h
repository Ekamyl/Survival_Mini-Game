#pragma once 


#include "physics.h"
#include "window.h"
#include "camera.h"

#define BACKGROUND_WIDTH 2304
#define BACKGROUND_HEIGHT 1296

#define GROUND_WIDTH BACKGROUND_WIDTH
#define GROUND_HEIGHT (WINDOW_HEIGHT / 4)

extern SDL_Renderer * renderer ;

typedef struct {
    StaticBody_t ground ;
    SDL_Texture * background ;
} Map_t ;


Map_t * map_constructor () ;
void map_destructor (Map_t ** map) ;
void draw_map (Map_t * map, Camera_t * camera) ;