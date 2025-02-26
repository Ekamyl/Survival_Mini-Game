#include "../include/lib.h"
#include "../include/main.h"
#include "../include/map.h"
#include "../include/texture_loader.h"


int rect_is_null (SDL_Rect rect) {
    return (rect.x == -1);
}

void set_rect_null (SDL_Rect * rect) {
    rect->x = -1; 
    rect->y = -1; 
    rect->w = -1; 
    rect->h = -1;  
}

Rectangle_t return_null () {
    Rectangle_t null = {0, 0, 0, 0};

    return null;
}

Rectangle_t return_ground () {
    Rectangle_t ground = {
        .x = 0,
        .y = BACKGROUND_HEIGHT - GROUND_HEIGHT,
        .width = GROUND_WIDTH,
        .height = GROUND_HEIGHT
    };

    return ground;
}

void init_elements_scene0 (Map_t * map){
    map->listElements[ERROR_WINDOW].hidden = TRUE;

    map->listElements[ICON_GAME].position.x = 50 + (rand() % 30 * 8);
    map->listElements[ICON_GAME].position.y = 50 + (rand() % 30 * 8);
}

/**
 * Renvoi la liste des Objet_t de la scene actuel. 
 * Recupere les donnes des Objet_t dans un fichier .txt
 */
DesktopElement_t * load_elements(int nbObject) {
    
    DesktopElement_t * list = malloc(sizeof(DesktopElement_t) * nbObject);

    char fileName[128];
    sprintf(fileName, "assets/donneesObjectScene%d.txt", gameStatus.scene);

    int x, y, w, h ;
    char buffer[256];

    FILE * file = fopen(fileName, "r");
    
    printf("srcrect du fichier %s :\n", fileName);
    for (int i = 0; i < nbObject; i++) {
        fscanf(file, "{%d, %d, %d, %d}", &x, &y, &w, &h);
        fgets(buffer, sizeof(buffer), file);
        
        list[i].srcrect.x = x;
        list[i].srcrect.y = y;
        list[i].srcrect.w = w;
        list[i].srcrect.h = h;

        list[i].hidden = FALSE;
        list[i].clicked = FALSE;
        list[i].dragged = FALSE;
        
        printf("x = %d; y = %d; w = %d; h = %d\n", list[i].srcrect.x, list[i].srcrect.y, list[i].srcrect.w, list[i].srcrect.h = h);
    }

    
    printf("dstrect du fichier %s :\n", fileName);
    for (int i = 0; i < nbObject; i++) {
        fscanf(file, "{%d, %d, %d, %d}", &x, &y, &w, &h);
        fgets(buffer, sizeof(buffer), file);

        list[i].position.x = x;
        list[i].position.y = y;
        list[i].position.w = w;
        list[i].position.h = h;

        printf("x = %d; y = %d; w = %d; h = %d\n", list[i].position.x, list[i].position.y, list[i].position.w, list[i].position.h = h);
    }

    fclose(file);

    return list;
}

Map_t * map_constructor () {
    Map_t * map = malloc(sizeof(Map_t));
    if (map == NULL) {
        printf("Erreur malloc map : %s\n", SDL_GetError());
        return NULL;
    }
    
    // donne un zone de cillison pour le sol 
    map->ground = return_ground();

    // charge l'image de fond
    map->background = load_png("assets/desktop_glitch.png");
    if (map->background == NULL) {
        return NULL;
    }

    // alloue de la memoire pour le tableau d'objets present sur la map 
    map->nbObject = 8;
    map->listElements = load_elements(map->nbObject);

    // // charge texture objet 
    map->objectsTexture = load_png("assets/spritesheetScene0.png");


    return map;
}

void map_destructor (Map_t ** map) {
    SDL_DestroyTexture((*map)->background);
    SDL_DestroyTexture((*map)->objectsTexture);
    
    free((*map)->listElements);
    (*map)->listElements = NULL;
    free(*map);
    *map = NULL;
}