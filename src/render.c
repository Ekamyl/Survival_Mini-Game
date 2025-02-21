#include "../include/lib.h"
#include "../include/main.h"
#include "../include/texture_loader.h"
#include "../include/map.h"
#include "../include/camera.h"
#include "../include/player.h"


void draw_map (Map_t * map, Camera_t * camera) {
    SDL_Rect srcrect = {camera->x, camera->y, camera->width, camera->height};
    if ((srcrect.x + srcrect.w) > BACKGROUND_WIDTH) srcrect.x = BACKGROUND_WIDTH - srcrect.w;
    
    Rectangle_t rec = map->ground.rec;
    SDL_Rect dstrect = {rec.x, rec.y, rec.width, rec.height}; // pour dessiner la zone de collision du sol 
    
    // dessine la zone de collision du sol 
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // SDL_RenderFillRect(renderer, &dstrect);

    SDL_RenderCopy(renderer, map->background, &srcrect, NULL);
}


static SDL_RendererFlip flip ;
void draw_player (Player_t * player, Camera_t * camera) {
    if (player->body.vx > 0) {
        flip = SDL_FLIP_NONE;
        if (player->body.vx == player->vMax)
            player->actionState = RUN;
        else 
            player->actionState = WALK;
    }
    else if (player->body.vx < 0) {
        flip = SDL_FLIP_HORIZONTAL;
        if (player->body.vx == -player->vMax)
            player->actionState = RUN;
        else 
            player->actionState = WALK;
    }
    else {
        player->actionState = IDLE;
        if (player->animState >= NB_IDLE_ANIM) 
            player->animState = 0;
    }

    Rectangle_t rec = player->body.rec;
    SDL_Rect dstrect = {rec.x - camera->x, rec.y, rec.width, rec.height};
    SDL_Rect srcrect = {PLAYER_SPRITE_WIDTH * player->animState + 20, PLAYER_SPRITE_HEIGHT * player->actionState, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_HEIGHT};


    SDL_RenderCopyEx(renderer, player->texture, &srcrect, &dstrect, 0, NULL, flip);

    // dessine la zone de collision du player 
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &dstrect);
}


static SDL_Texture * noiseTexture ;
int generate_noise_texture(int width, int height) {
    
    // creer surface
    SDL_Surface * surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA8888);
    if (surface == NULL) {
        printf("Erreur generate surface for noise texture : %s\n", SDL_GetError());
        return 1 ;
    }


    // change la valeur des pixels 
    Uint32 *pixels = (Uint32 *)surface->pixels;
    for (int i = 0; i < width * height; i++) {
        if (rand() % 10 > 4) {
            Uint8 noise = rand() % 256;
            pixels[i] = SDL_MapRGBA(surface->format, noise, noise, noise, 100); // Alpha faible
        }
    }

    // creer texture a partir de la surface 
    noiseTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (noiseTexture == NULL) {
        printf("Erreur generate texture for noise texture : %s\n", SDL_GetError());
        return 1 ;
    }
    
    // libere les surface
    SDL_FreeSurface(surface);

    return 0;
}
void destroy_noise_texture () {
    SDL_DestroyTexture(noiseTexture);
}


void apply_glitch(SDL_Texture *texture, int width, int height) {
    
    int axis = rand() % 2 ; // 0 pour horizontal, 1 pour vertical

    int maxRender = 30;
    for (int i = 0; i < maxRender; i++) {
        
    }
}


// affiche l'ecran 
// retourne 1 en cas d'erreu ou 0 si aucune erreur 
int draw (Camera_t * camera, Player_t * player, Map_t * map) {
    
    // si player dans la zone de glitch, affiche glitch visuel  
    if (player->body.rec.x > (BACKGROUND_WIDTH - camera->width / 2)) { 
        
        // render la map
        draw_map(map, camera);
        if (gameStatus.frameCount > 30) {
            apply_glitch(map->background, BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
        }

        // render le player 
        draw_player (player, camera);

        SDL_Rect srcrect = {(WINDOW_WIDTH / 4) * (rand() % 4), (WINDOW_HEIGHT / 4) * (rand() % 4), WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4};
        SDL_RenderCopy(renderer, noiseTexture, &srcrect, NULL);
    }
    else {
        // render la map
        draw_map(map, camera);

        // render le player 
        draw_player (player, camera);
    }

    return 0;
}