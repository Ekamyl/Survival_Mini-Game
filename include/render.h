#pragma once 


#include "main.h"
#include "lib.h"
#include "player.h"
#include "map.h"
#include "camera.h"
#include "desktop.h"

extern SDL_Renderer * renderer ;
extern GameStatus_t gameStatus ;


typedef enum Direction_u {UP, DOWN, LEFT, RIGHT} Direction_t ;
typedef enum TextAnimation_u {LEFT_RIGHT} TextAnimation_t ; 

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

/**
 * Structure de gestion de l'animation des textes à afficher. L'animation d'affichage de chaque texte est joué une seule fois.
 */
typedef struct Text_u {

    // Texture à afficher 
    SDL_Texture * texture ;         // Message en texture 
    SDL_Color textColor ;           // Couleur du texte 
    SDL_Rect position ;             // Position du message sur l'écran 
    int needChange ;                // TRUE = texture doit etre changé, FALSE = texture à jour 
    
    // Le texte peut avoir une ombre (optionnel)
    int hollow ;                    // TRUE = le texte à une ombre, FALSE = le texte n'a pas d'ombre 
    SDL_Color hollowColor ;         // Couleur de l'ombre 
    Direction_t hollowDir ;         // Dans quelle direction se dirige l'ombre 
    
    // Texte 
    TTF_Font * font ;               // Police de caractère
    char * string ;                 // Texte à afficher
    int len ;                       // Longueur de la chaine de caractere 
    int numLettres ;                // Nombre de lettres
    
    // Variables propre aux animations 
    TextAnimation_t anim ;          // Type d'animation
    int frameCount ;                // Compteur interne
    int currentLetter ;             // Derniere lettre du texte ayant été animée 
    int animationSpeed ;            // Nombre de frames avant changement
    int animationFinished ;         // TRUE = animation terminé, FALSE = animation en cours 
} Text_t ; 
 

err_t draw_text (const char * text, TTF_Font * font, SDL_Color * color, SDL_Rect * dstrect) ;
void change_text (TTF_Font * newFont, SDL_Color * newColor, SDL_Rect * newPos, SDL_Color * newHollowColor) ;
void update_text () ;
void draw_map (Map_t * map, Camera_t * camera) ;
void draw_desktop (Desktop_t * desktop) ;
int draw (Camera_t * camera, Player_t * player, Map_t * map) ;
int generate_noise_texture(int width, int height) ;
void destroy_noise_texture () ;
int generate_desktop_glitch_texture () ;
void destroy_desktop_glitch_texture () ;