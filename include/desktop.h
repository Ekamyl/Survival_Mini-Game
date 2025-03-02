#pragma once 

#include "lib.h"

typedef struct DesktopElement_u {
    SDL_Rect srcrect ;
    SDL_Rect position ;
    int hidden ;        // TRUE or FALSE 
    int clicked ;       // TRUE or FALSE 
    int dragged ;       // TRUE or FALSE 
} DesktopElement_t ; 

typedef struct Desktop_u {
    SDL_Texture * background ;
    DesktopElement_t * elements ;
}  Desktop_t ;