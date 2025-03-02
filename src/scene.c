#include "../include/lib.h"
#include "../include/main.h"
#include "../include/window.h"
#include "../include/player.h"
#include "../include/map.h"
#include "../include/camera.h"
#include "../include/render.h"
#include "../include/scene.h"


/**
 * Detruis la scene 
 */
void destroy_scene (Scene_t ** scene) {

    // libere memoire chaine caractere 
    free((*scene)->name);
    (*scene)->name = NULL;

    // libere memoire structure Scene_t
    free(*scene);
    *scene = NULL;
}


/**
 * Creer une nouvelle scene 
 */
Scene_t * create_scene (char * name, int (*load) (Scene_t *, void **), int (*unLoad) (Scene_t *, void **),
                        int (*handleEvents) (Scene_t *, void **), int (*update) (Scene_t *, void **), 
                        int (*render) (Scene_t *, void **)) {
    
    // alloue memoire scene
    Scene_t * scene = malloc(sizeof(Scene_t));
    if (scene == NULL) {
        fprintf(stderr, "Erreur malloc scene : %s\n", name);
        return NULL;
    }

    
    // recopie du parametre name dans la scene 
    int len = strlen(name);
    scene->name = malloc(sizeof(char) * len);
    if (scene->name == NULL) {
        fprintf(stderr, "Erreur malloc name de scene : %s\n", name);
        return NULL;
    }
    strcpy(scene->name, name);


    // initialise les pointeurs sur fonctions 
    scene->load = load ;
    scene->unLoad = unLoad ;
    scene->handleEvents = handleEvents ;
    scene->update = update ;
    scene->render = render ;

    return scene;
}


void init_scene_manager (SceneManager_t * manager) {
    
}


/**
 * Change de scenes 
 */
void changeScene (SceneManager_t * manager, char * newScene) {
    
    // si la nouvelle scene est identique a la scene actuelle
    if (strcmp(manager->scenes[manager->index].name, newScene) == 0) return;

    // recherche de l'index de la nouvelle scene 
    int newIndex = -1 ;
    for (int i = 0; i < MAX_SCENES; i++) {
        if (strcmp(manager->scenes[i].name, newScene) == 0) {
            newIndex = i ;
        }
    }

    // si aucune des scenes presentes dans la listes des scenes ne correspond a newScene 
    if (newIndex == -1) {
        printf("Changement de scene impossible, \"%s\" introuvable\n", newScene);
        return ;
    }

    // variable temporaire de la scene actuelle 
    int index = manager->index ;
    Scene_t * scene = &manager->scenes[index] ;
    
    // decharge les data de la scene actuelle 
    if (scene && scene->unLoad) {
        scene->unLoad(scene, scene->data);
    }

    // change l'index de la scene courante de manager, et les variables temporaire de la scene actuelle
    manager->index = newIndex ;
    index = newIndex ;
    scene = &manager->scenes[index] ;

    // charge les data de la nouvelle scene
    if (scene && scene->load) {
        scene->load(scene, scene->data);
    }
}


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

    for (int i = 0; i < map->nbObject; i++) {
        if (map->listElements[i].hidden == FALSE && SDL_PointInRect(&mouse, &map->listElements[i].position)) {

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
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 231, 244, 244, 60);

    for (int i = 0; i < map->nbObject; i++) {
        if (map->listElements[i].hidden == FALSE && SDL_PointInRect(&mouse, &map->listElements[i].position)) {
            printf("bon\n");
            SDL_RenderFillRect(renderer, &map->listElements[i].position);
        }
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
                buttonClicked = 1;
                clicks = event.button.clicks;
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
                        printf("INFO :\nplayer x, y, vx, vy : %f %f %f %f\ncamera x, y : %f %f\n", player->body.position.x, player->body.position.y, player->body.vx, player->body.vy, camera->x, camera->y);
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