#include "../include/lib.h"
#include "../include/main.h"
#include "../include/window.h"
#include "../include/player.h"
#include "../include/map.h"
#include "../include/camera.h"
#include "../include/render.h"
#include "../include/scene.h"


int play_scene0 (Camera_t * camera, Player_t * player, Map_t * map) {

    SDL_Event event ;
    uint32_t buttonClicked = FALSE;
    uint8_t clicks = 0;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT : 
                gameStatus.running = FALSE;
                break;
            case SDL_KEYDOWN :
                switch (event.key.keysym.sym) {
                    case SDLK_q :
                        break;
                    case SDLK_d :
                        break;
                    case SDLK_SPACE :
                        break;
                    case SDLK_BACKSPACE : 
                        gameStatus.running = FALSE;
                    default :
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN :
                buttonClicked = SDL_MOUSEBUTTONDOWN;
                clicks = event.button.clicks;
                break;
            case SDL_MOUSEBUTTONUP :
                buttonClicked = SDL_MOUSEBUTTONUP;
                break;
        }
    }
    
    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear (renderer); 
    
    // position carre vert 
    int cubeSize = 150;
    SDL_Rect rect = {(camera->width / 2) - (cubeSize / 2), (camera->height / 2) - (cubeSize / 2), cubeSize, cubeSize};
    
    // affiche carre vert en fonction de la position du curseur 
    SDL_Point mouse ;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    if (SDL_PointInRect(&mouse, &rect)) {
        SDL_SetRenderDrawColor(renderer, 0, 200, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
        
        // si boutton clicker sur carre vert change scene 
        if (buttonClicked && clicks == 2) gameStatus.scene = 1;
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0, 100, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
    }

    // Mettre à jour l'écran
    SDL_RenderPresent (renderer);

    // recupere les touche presser 
    const uint8_t * keys = SDL_GetKeyboardState(NULL);


    if (keys[SDL_SCANCODE_SPACE]) {
        gameStatus.scene = 1;
    }
}


int play_scene1 (Camera_t * camera, Player_t * player, Map_t * map) {

    SDL_Event event ;
    uint32_t buttonClicked = FALSE;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT : 
                gameStatus.running = FALSE;
                break;
            case SDL_KEYDOWN :
                switch (event.key.keysym.sym) {
                    case SDLK_q :
                        break;
                    case SDLK_d :
                        break;
                    case SDLK_SPACE :
                        break;
                    case SDLK_BACKSPACE : 
                        gameStatus.running = FALSE;
                    default :
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN :
                buttonClicked = SDL_MOUSEBUTTONDOWN;
                break;
            case SDL_MOUSEBUTTONUP :
                buttonClicked = SDL_MOUSEBUTTONUP;
                break;
        }
    }

    const uint8_t * keys = SDL_GetKeyboardState(NULL);
    handle_input(keys, player);

    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear (renderer); 

    // met a jour la position des objets dynamique 
    update_player(player, &map->ground);
    update_camera(camera, player);

    // dessine le rendu 
    if (draw (camera, player, map)) {
        gameStatus.running = 0;
    }

    // Mettre à jour l'écran
    SDL_RenderPresent (renderer);

    gameStatus.updateCount++;

    if (gameStatus.updateCount == 5) {
        gameStatus.updateCount = 0;
        update_player_anim_state (player);
    }        
}