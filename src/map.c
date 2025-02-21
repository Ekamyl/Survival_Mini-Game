#include "../include/lib.h"
#include "../include/main.h"
#include "../include/map.h"
#include "../include/texture_loader.h"
#include "../include/camera.h"


Map_t * map_constructor () {
    Map_t * map = malloc(sizeof(Map_t));
    if (map == NULL) {
        printf("Erreur malloc map : %s\n", SDL_GetError());
        return NULL;
    }
    
    map->ground.rec.x = 0; 
    map->ground.rec.y = (WINDOW_HEIGHT / 4) * 3;
    map->ground.rec.width = GROUND_WIDTH;
    map->ground.rec.height = GROUND_HEIGHT;

    map->background = load_png("assets/background_grey.png");
    if (map->background == NULL) {
        return NULL;
    }

    return map;
}

void map_destructor (Map_t ** map) {
    SDL_DestroyTexture((*map)->background);

    free(*map);
    *map = NULL;
}