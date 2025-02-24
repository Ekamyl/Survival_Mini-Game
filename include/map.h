#pragma once 


#include "physics.h"
#include "window.h"

extern GameStatus_t gameStatus ;

#define BACKGROUND_WIDTH 2304
#define BACKGROUND_HEIGHT 1296

#define GROUND_WIDTH BACKGROUND_WIDTH
#define GROUND_HEIGHT (WINDOW_HEIGHT / 4)

#define ICON_LOCK 0
#define ICON_GAME 1
#define ICON_DOC 2
#define ERROR_WINDOW 3
#define TOP_BORDER 4
#define LEFT_BORDER 5
#define RIGHT_BORDER 6
#define BOTTOM_BORDER 7

typedef struct Objet_u {
    SDL_Rect srcrect ;
    SDL_Rect position ;
} Objet_t ;

typedef struct Map_u {
    SDL_Texture * background ;

    Rectangle_t ground ;
    
    SDL_Texture * objectsTexture ;
    Objet_t * listObject ;
    int nbObject;
} Map_t ;


StaticBody_t constructor_listObject (int numScene);
Map_t * map_constructor () ;
void map_destructor (Map_t ** map) ;
void set_rect_null (SDL_Rect * rect) ;
int rect_is_null (SDL_Rect rect) ;