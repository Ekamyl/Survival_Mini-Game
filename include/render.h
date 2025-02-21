#pragma once 


#include "lib.h"
#include "main.h"
#include "player.h"
#include "map.h"
#include "camera.h"

extern SDL_Renderer * renderer ;
extern GameStatus_t gameStatus ;


void draw_player (Player_t * player, Camera_t * camera);
void draw_map (Map_t * map, Camera_t * camera);
int generate_noise_texture(int width, int height);
int draw (Camera_t * camera, Player_t * player, Map_t * map);
void destroy_noise_texture ();