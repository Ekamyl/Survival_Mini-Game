#pragma once 


#include "lib.h"
#include "player.h"
#include "map.h"
#include "camera.h"
#include "desktop.h"

extern SDL_Renderer * renderer ;
extern GameStatus_t gameStatus ;


void draw_map (Map_t * map, Camera_t * camera);
int draw (Camera_t * camera, Player_t * player, Map_t * map);
int generate_noise_texture(int width, int height);
void destroy_noise_texture ();