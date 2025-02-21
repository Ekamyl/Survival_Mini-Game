#include "../include/lib.h"
#include "../include/main.h"
#include "../include/map.h"
#include "../include/texture_loader.h"


StaticBody_t return_null () {
    StaticBody_t null = {0, 0, 0, 0};

    return null;
}

StaticBody_t return_ground () {
    StaticBody_t ground = {
        .rec.x = 0,
        .rec.y = (WINDOW_HEIGHT / 4) * 3,
        .rec.width = GROUND_WIDTH,
        .rec.height = GROUND_HEIGHT
    };

    return ground;
}

Map_t * map_constructor () {
    Map_t * map = malloc(sizeof(Map_t));
    if (map == NULL) {
        printf("Erreur malloc map : %s\n", SDL_GetError());
        return NULL;
    }
    
    map->ground = return_ground();

    map->background = load_png("assets/background.png");
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