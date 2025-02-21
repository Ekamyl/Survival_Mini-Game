#include "../include/lib.h"
#include "../include/main.h"
#include "../include/texture_loader.h"
#include "../include/map.h"
#include "../include/camera.h"
#include "../include/player.h"


void draw_map (Map_t * map, Camera_t * camera) {
    SDL_Rect srcrect = {camera->x, camera->y, camera->width, camera->height};
    if ((srcrect.x + srcrect.w) > BACKGROUND_WIDTH) srcrect.x = BACKGROUND_WIDTH - srcrect.w;
    
    SDL_RenderCopy(renderer, map->background, &srcrect, NULL);

    // dessine la zone de collision du sol 
    // SDL_Rect dstrect = {0, map->ground.rec.y, WINDOW_WIDTH, map->ground.rec.height}; 
    
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    // SDL_RenderFillRect(renderer, &dstrect);
}


static SDL_RendererFlip flip ;
void draw_player (Player_t * player, Camera_t * camera) {

    // definie l'action que fait le personnage (courir, marcher, sur place, sauter)
    if (player->body.onGround == FALSE) {
        // definie l'anim state pour connaitre le sprite d'animation de saut a affiché
        player->animState = player->body.jump > 0 ? (JUMP_FORCE - player->body.jump) / (JUMP_FORCE / NB_JUMP_ANIM) : NB_JUMP_ANIM - 1 ;
        player->actionState = JUMP;

        if (player->body.vx < 0) flip = SDL_FLIP_HORIZONTAL;
        else flip = SDL_FLIP_NONE ;
    }
    else if (player->body.vx > 0) {
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
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // SDL_RenderDrawRect(renderer, &dstrect);
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


void apply_glitch(Camera_t * camera, SDL_Texture *texture, int width, int height) {
    
    int axis = rand() % 2 ; // 0 pour horizontal, 1 pour vertical

    float widthMax = WINDOW_WIDTH / 4, widthMin = WINDOW_WIDTH / 8;
    float heightMax = WINDOW_HEIGHT / 4, heightMin = WINDOW_HEIGHT / 8;
    int gap = 10;
    int maxRender = 40;
    for (int i = 0; i < maxRender; i++) {
        if (axis == 0) {        // decalage pixel a l'horizontal 
            float width = rand() % (int) (widthMax - widthMin) + widthMin ;
            float height = gap ;
            float x = rand() % (int) (WINDOW_WIDTH - width) ;
            float y = height * (rand() % (int) ((WINDOW_HEIGHT / height) - 2) + 1) ;

            gap = (rand() % 2 ? gap : -gap) ;      // distance decalage de la ranger de pixel  

            SDL_Rect srcrect = {x + camera->x, y + camera->y, width, height};
            SDL_Rect dstrect = {x, y + gap, width, height};
            SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
        }
        else {
            float width = gap ;
            float height = rand() % (int) (heightMax - heightMin) + heightMin ;
            float x = width * (rand() % (int) ((WINDOW_WIDTH / width) - 2) + 1) ;
            float y = rand() % (int) (WINDOW_HEIGHT - height) ;

            gap = (rand() % 2 ? gap : -gap) ;      // distance decalage de la ranger de pixel  

            SDL_Rect srcrect = {x + camera->x, y + camera->y, width, height};
            SDL_Rect dstrect = {x + gap, y, width, height};
            SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
        }
    }

    
}


// affiche l'ecran 
// retourne 1 en cas d'erreu ou 0 si aucune erreur 
int draw (Camera_t * camera, Player_t * player, Map_t * map) {
    
    // si player dans la zone de glitch, affiche glitch visuel  
    if (player->body.rec.x > (BACKGROUND_WIDTH - camera->width / 2)) { 
        
        // render la map
        draw_map(map, camera);
        
        // render le player 
        draw_player (player, camera);
        
        // applique un effet de glitch sur l'ecran
        if (rand() % 3 == 0) {
            apply_glitch(camera, map->background, BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
        }

        // affiche un bruit visuel, ressemble a l'ecran gris des tv cathodique 
        // SDL_Rect srcrect = {(WINDOW_WIDTH / 4) * (rand() % 4), (WINDOW_HEIGHT / 4) * (rand() % 4), WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4};
        // SDL_RenderCopy(renderer, noiseTexture, &srcrect, NULL);
    }
    else {
        // render la map
        draw_map(map, camera);

        // render le player 
        draw_player (player, camera);
    }

    return 0;
}