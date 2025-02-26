#pragma once 


extern SDL_Renderer * renderer ;
extern GameStatus_t gameStatus ;

typedef struct Camera_u Camera_t ;
typedef struct Player_u Player_t ;
typedef struct Map_u Map_t ; 


void init_scene(Camera_t * camera, Player_t * player, Map_t * map);
int play_scene0 (Camera_t *, Player_t *, Map_t *);
int play_scene1 (Camera_t *, Player_t *, Map_t *);
