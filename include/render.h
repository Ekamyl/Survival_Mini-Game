#pragma once 


#include "lib.h"
#include "player.h"
#include "map.h"
#include "camera.h"
#include "desktop.h"

extern SDL_Renderer * renderer ;
extern GameStatus_t gameStatus ;

/**
 * Structure de gestion de l'animation pour chacun des objets ou entités devant etre animée.
 */
typedef struct Animation_u {
    SDL_Texture * spritesheet;      // Texture globale contenant tous les sprites
    int startX, startY;             // Position de la première frame dans le spritesheet
    int frameWidth, frameHeight;    // Taille d'une frame
    int numFrames;                  // Nombre total de frames d'animation
    int currentFrame;               // Frame actuelle de l'animation 
    int animationSpeed;             // Nombre de frames avant changement
    int frameCount;                 // Compteur interne
    int loop;                       // 1 = animation en boucle, 0 = joue une seule fois
    int playing;                    // 1 = animation active, 0 = arrêtée
} Animation_t ;


int draw_text (const char * text, TTF_Font * font, SDL_Color * color) ;
void draw_map (Map_t * map, Camera_t * camera) ;
void draw_desktop (Desktop_t * desktop) ;
int draw (Camera_t * camera, Player_t * player, Map_t * map) ;
int generate_noise_texture(int width, int height) ;
void destroy_noise_texture () ;
int generate_desktop_glitch_texture () ;
void destroy_desktop_glitch_texture () ;