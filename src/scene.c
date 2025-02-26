#include "../include/lib.h"
#include "../include/main.h"
#include "../include/window.h"
#include "../include/player.h"
#include "../include/map.h"
#include "../include/camera.h"
#include "../include/render.h"
#include "../include/scene.h"


/**
 * 
 */
void init_scene0(Camera_t * camera, Player_t * player, Map_t * map) {
    init_elements_scene0(map);
}


/**
 * 
 */
void init_scene(Camera_t * camera, Player_t * player, Map_t * map) {
    switch (gameStatus.scene) {
        case 0 : 
            init_scene0(camera, player, map) ;
            break;
        case 1 : 
            init_scene0(camera, player, map) ;
        default : 
            break;
    }
}


/**
 * renvoi l'indice de l'element de l'ecran qui a ete executée sinon renvoi -1 
 */
int element_update(Map_t * map, SDL_Event * event) {
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 231, 244, 244, 100);

    for (int i = 0; i < map->nbObject; i++) {
        if (map->listElements[i].hidden == FALSE && SDL_PointInRect(&mouse, &map->listElements[i].position)) {
            SDL_RenderFillRect(renderer, &map->listElements[i].position);

            // si le joueur clique sur l'icone 
            if (event->button.type == SDL_MOUSEBUTTONDOWN) {
                map->listElements[i].dragged = TRUE;
                map->listElements[i].clicked = TRUE;
            }
            else if (event->button.type == SDL_MOUSEBUTTONUP) {
                map->listElements[i].dragged = FALSE;
                map->listElements[i].clicked = TRUE;
            }
            // si double clique 
            if (event->button.clicks == 2) return i;
        }
        else {
            map->listElements[i].dragged = FALSE;
            map->listElements[i].clicked = FALSE;
        }
    }

    return -1;
}


/**
 * 
 */
void move_element (Map_t * map, SDL_Event * event) {
    for (int i = 0; i < map->nbObject; i++) {
        if (map->listElements[i].dragged == TRUE) {
            map->listElements[i].position.x += event->motion.xrel;
            map->listElements[i].position.y += event->motion.yrel;
        }
    }
}


/**
 * 
 */
int check_element_collision () {}


/**
 * 
 */
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
                printf("Bouton presser\n");
                element_update(map, &event);
                break;
            case SDL_MOUSEBUTTONUP :
                printf("Bouton lever\n");
                element_update(map, &event);
                break;
            case SDL_MOUSEMOTION : 
                move_element(map, &event);
                break;
            default : 
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
    
    
    // affiche le background test 
    draw(camera, player, map);
    
    // check la collision entre les element du bureau 
    // check_elements_collision(map);
    
    // Mettre à jour l'écran
    SDL_RenderPresent (renderer);

    // update position camera, se positionne sur un des 4 coins 
    update_camera_random(camera);

    // recupere les touche presser 
    const uint8_t * keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_SPACE]) {
        gameStatus.scene = 1;
    }

    return 0;
}

/**
 * 
 */
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
                        break;
                    case SDLK_f :
                        camera->followPlayer = (camera->followPlayer + 1) % 2; printf("changement follow\n");
                        break;
                    case SDLK_i :
                        printf("INFO :\nplayer x, y : %f %f\ncamera x, y : %f %f\n", player->body.rec.x, player->body.rec.y, camera->x, camera->y);
                        break;
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
    
    return 0;
}