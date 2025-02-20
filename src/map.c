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
    map->ground.rec.y = WINDOW_HEIGHT / 4 * 3;
    map->ground.rec.width = GROUND_WIDTH;
    map->ground.rec.height = GROUND_HEIGHT;

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

void draw_map (Map_t * map, Camera_t * camera) {
    SDL_Rect srcrect = {camera->x, camera->y, camera->width, camera->height};
    if ((srcrect.x + srcrect.w) > BACKGROUND_WIDTH) srcrect.x = BACKGROUND_WIDTH - srcrect.w;
    
    Rectangle_t rec = map->ground.rec;
    SDL_Rect dstrect = {rec.x, rec.y, rec.width, rec.height}; // pour dessiner la zone de collision du sol 
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // SDL_RenderFillRect(renderer, &dstrect);

    SDL_RenderCopy(renderer, map->background, &srcrect, NULL);
}