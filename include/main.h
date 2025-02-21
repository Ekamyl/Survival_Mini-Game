#pragma once 


#define TRUE 1
#define FALSE 0

#define FPS 60
#define FRAME_DELAY (1000 / FPS)

typedef struct {
    int running ; 
    int level ;
    int glitchedScreen ; 
    int frameCount ;
    SDL_KeyCode keyPressed ;
} GameStatus_t ; 