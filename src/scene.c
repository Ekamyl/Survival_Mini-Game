#include "../include/lib.h"
#include "../include/main.h"
#include "../include/window.h"
#include "../include/player.h"
#include "../include/map.h"
#include "../include/camera.h"
#include "../include/render.h"
#include "../include/scene.h"
#include "../include/desktop.h"



// #######################################################################################
// ############################## FONCTIONS SCENE DESKTOP ################################
// #######################################################################################


/**
 * @brief Charge les données de la scène "DESKTOP" et les stocke dans `self->data`.
 * 
 * Cette fonction initialise la structure `Scene_t` en allouant et en stockant les données 
 * nécessaires à la scène "DESKTOP". Ces données incluent :
 * - `self->data[0]` : Un entier (`int *len`) indiquant le nombre d'éléments stockés.
 * - `self->data[1]` : Un pointeur vers la structure `Desktop_t`.
 * 
 * Si `self->data` est `NULL`, un tableau dynamique de `void *` est alloué.
 * 
 * @param self Pointeur vers la structure `Scene_t` représentant la scène actuelle.
 * @return int Retourne `1` en cas de succès, ou `0` en cas d'échec.
 * 
 * @note L'appelant est responsable de libérer `self->data`, `len` et `desktop` après utilisation.
 * @warning En cas d'échec de l'allocation mémoire ou du chargement de `desktop`, la fonction retourne `0`.
 */
int DESKTOP_load(Scene_t *self) {

    if (self == NULL) {
        fprintf(stderr, "Erreur: `self` est NULL\n");
        return 0;
    }

    // Allocation et initialisation du compteur d'éléments
    int *len = malloc(sizeof(int));
    if (len == NULL) {
        fprintf(stderr, "Erreur: allocation mémoire échouée pour `len`\n");
        return 0;
    }
    *len = 4;

    // Vérification et allocation dynamique de `self->data` si NULL
    if (self->data == NULL) {
        self->data = malloc(sizeof(void *) * (*len));
        if (self->data == NULL) {
            fprintf(stderr, "Erreur: allocation mémoire échouée pour `self->data`\n");
            free(len);
            return 0;
        }
    }

    // Création du bureau (Desktop_t)
    Desktop_t *desktop = create_desktop("assets/backgroundDesktopScene.png", "assets/objectsDesktopScene.png", "data/donneesObjetsDesktopScene.csv", NB_ELEM_DESKTOP_SCENE);
    if (desktop == NULL) {
        fprintf(stderr, "Erreur: création de `desktop` échouée\n");
        free(len);
        free(self->data);
        self->data = NULL;
        return 0;
    }

    // Création font (TTF_Font) 
    TTF_Font * font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", 23) ;
    if (font == NULL) {
        fprintf(stderr, "Erreur open font : assets/PressStart2P-Regular.ttf\n");
        free(len);
        destroy_desktop(&desktop);
        free(self->data);
        self->data = NULL;
    } 

    // Création couleur font (SDL_Color)  
    SDL_Color * color = malloc(sizeof(SDL_Color)) ;
    if (color == NULL) {
        fprintf(stderr, "Erreur malloc coor\n");
        free(len);
        destroy_desktop(&desktop);
        TTF_CloseFont(font);
        free(self->data);
        self->data = NULL;
    }
    
    // Initialisation de la couleur du font 
    color->r = 255 ; 
    color->g = 255 ; 
    color->b = 255 ; 
    color->a = 100 ; 

    // Initialisation element du bureau (DesktopElement_t)
    desktop->elements[3].hidden = TRUE ;    // Annule affichage icone message d'erreur  

    // Stockage dans `self->data`
    self->data[0] = len;
    self->data[1] = desktop;
    self->data[2] = font ;
    self->data[3] = color ;

    printf("[INFO] : Chargement des données DESKTOP réussi\n");
    return 1; 
}


/**
 * @brief Décharge les données de la scène "DESKTOP" et libère la mémoire allouée.
 * 
 * Cette fonction libère les ressources allouées dans `DESKTOP_load()`, notamment :
 * - `self->data[0]` : Le pointeur `int *len`.
 * - `self->data[1]` : La structure `Desktop_t`, y compris `desktop->elements` et `desktop->background`.
 * - `self->data` : Le tableau de `void *`.
 * 
 * @param self Pointeur vers la structure `Scene_t` contenant les données de la scène.
 * @return int Retourne `1` en cas de succès, ou `0` si `self` est `NULL`.
 */
int DESKTOP_unLoad(Scene_t *self) {
    if (self == NULL) {
        fprintf(stderr, "Erreur: `self` est NULL\n");
        return 0;
    }

    if (self->data == NULL) {
        fprintf(stderr, "Aucune donnée à libérer dans `self->data`\n");
        return 1;
    }

    // Récupération du nombre d'éléments stockés (self->data[0])
    int *len = (int *)self->data[0];
    if (len != NULL) {
        free(len);
    }

    // Libération de la structure Desktop_t (self->data[1])
    Desktop_t *desktop = (Desktop_t *)self->data[1] ;
    destroy_desktop(&desktop);

    // Libération du font (self->data[2])
    TTF_Font * font = (TTF_Font *)self->data[2] ;
    TTF_CloseFont(font);

    // Libération de la structure SDL_Color (self->data[3])
    SDL_Color * color = (SDL_Color *)self->data[3] ;
    free(color);

    // Libération du tableau `self->data` et mise à NULL
    free(self->data);
    self->data = NULL;

    printf("[INFO] : Déchargement des données DESKTOP réussi\n");
    return 1;
}


int DESKTOP_handleEvents (Scene_t * self, SDL_Event * event) {

    Desktop_t * desktop = self->data[1] ;
    int continuePlaying = TRUE ;
    
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT :
                continuePlaying = FALSE ;
                break;
            case SDL_KEYDOWN :
                switch (event->key.keysym.sym) {
                    case SDLK_q :
                        break;
                    case SDLK_d :
                        break;
                    case SDLK_SPACE :
                        break;
                    case SDLK_BACKSPACE : 
                        continuePlaying = FALSE;
                    default :
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN :
                element_update(desktop, event);
                break;
            case SDL_MOUSEBUTTONUP :
                element_update(desktop, event);
                break;
            case SDL_MOUSEMOTION : 
                move_element(desktop, event);
                break;
            default : 
                break;
        }
    }

    return continuePlaying; 
}


int DESKTOP_update (Scene_t * self) {
    return 1; 
}


int DESKTOP_render (Scene_t * self) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    Desktop_t * desktop = (Desktop_t *) self->data[1] ;
    draw_desktop(desktop);

    char text[128] = "ABCDEFGHIJKLMOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n0123456789" ;
    if (rand() % 10 > 4) draw_text(text, (TTF_Font *)self->data[2], (SDL_Color *)self->data[3]);

    SDL_RenderPresent(renderer);

    return 1; 
}



// #######################################################################################
// ############################## FONCTIONS SCENE DESKTOP ################################
// #######################################################################################



int LEVEL1_load (Scene_t * self) {
    return 1; 
}


int LEVEL1_unLoad (Scene_t * self) {
    return 1; 
}


int LEVEL1_handleEvents (Scene_t * self, SDL_Event * event) {
    return 1; 
}


int LEVEL1_update (Scene_t * self) {
    return 1; 
}


int LEVEL1_render (Scene_t * self) {
    return 1; 
}


// #######################################################################################
// ############################## FONCTIONS DE MANIP SCENES ##############################
// #######################################################################################


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
Scene_t * create_scene (char * name, int (*load) (Scene_t *), int (*unLoad) (Scene_t *),
                        int (*handleEvents) (Scene_t *, SDL_Event *), int (*update) (Scene_t *), 
                        int (*render) (Scene_t *)) {
    
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
    scene->data = NULL ;

    return scene;
}


/**
 * ##############################################################################################
 * ############################## FONCTIONS DE MANIP SCENE MANAGER ##############################
 * ##############################################################################################
 */


/**
 * Creer et initialise le scene manager 
 */
SceneManager_t * create_scene_manager () {

    // alloue memoire de la structure 
    SceneManager_t * manager = malloc(sizeof(SceneManager_t)) ;
    
    // initialise les variables 
    manager->index = -1;
    manager->sceneCount = 0;

    return manager ;
}


/**
 * Ajoute une scene dans la liste des scnenes du scene manager. Si la liste est complete ne produit 
 * aucun changement.
 */
void push_scene (SceneManager_t * manager, Scene_t * newScene) {

    // si la liste ne peut prendre de nouvelles scenes 
    if (manager->sceneCount == MAX_SCENES) {
        printf("[INFO] : Liste scenes complete, ne peut ajouter Scene \"%s\"\n", newScene->name);
        return ;
    }

    // ajoute la scene apres la derniere scene dans la liste, et incremente le compteur de scene 
    manager->scenes[manager->sceneCount] = newScene ;

    manager->sceneCount++;
}


/**
 * Ajoute une scene dans la liste d'attente (attribut char * nextScene du scene manager). 
 * Apres le rendu de la frame actuelle, la scene courante sera la scene en attente.
 */
void request_scene_change (SceneManager_t * manager, char * name) {
    strcpy(manager->nextScene, name) ;
}


/**
 * @brief Change la scène active dans le gestionnaire de scènes.
 * 
 * Cette fonction met à jour la scène actuelle en fonction de `manager->nextScene`. 
 * - Si `nextScene` correspond à une scène existante, elle remplace la scène actuelle.  
 * - Si aucune scène ne correspond, la fonction affiche un message d'erreur et retourne.  
 * - Si aucune scène n'était active (`index < 0`), elle charge simplement la nouvelle scène.  
 * 
 * @param manager Pointeur vers le gestionnaire de scènes `SceneManager_t` contenant les scènes.
 * 
 * @note `manager->nextScene` doit être une chaîne valide contenant le nom de la scène cible.
 * @warning Vérifie que la scène existe avant de tenter un changement, sinon un message d'erreur est affiché.
 */
void change_scene(SceneManager_t *manager) {
    if (manager == NULL) {
        fprintf(stderr, "Erreur: `manager` est NULL\n");
        return;
    }

    // Stocke le nom de la nouvelle scène en attente
    char newScene[128];
    strcpy(newScene, manager->nextScene);

    // Recherche de l'index de la nouvelle scène dans `manager->scenes`
    int newIndex = -1;
    for (int i = 0; i < MAX_SCENES; i++) {
        if (strcmp(manager->scenes[i]->name, newScene) == 0) {
            newIndex = i;
            printf("[INFO] : Nouvelle scène trouvée: index = %d\n", newIndex);
            break;  // On arrête la recherche dès qu'on trouve la scène
        }
    }

    // Vérifie si la scène a été trouvée
    if (newIndex == -1) {
        printf("[INFO] : Changement de scène impossible : \"%s\" introuvable\n", newScene);
        return;
    }

    // Cas où aucune scène n'est actuellement jouée (`index < 0`)
    if (manager->index < 0) {
        Scene_t *scene = manager->scenes[newIndex];

        // Charge la nouvelle scène si elle a une fonction `load`
        if (scene && scene->load) {
            scene->load(scene);
        }

        // Met à jour l'index et réinitialise `nextScene`
        manager->index = newIndex;
        strcpy(manager->nextScene, "");

        printf("[INFO] : Changement de scène réussi: nouvelle scène = %s\n", newScene);

        return;
    }

    // Vérifie si la scène demandée est déjà la scène en cours
    if (strcmp(manager->scenes[manager->index]->name, newScene) == 0) {
        return;  // Rien à changer, on sort de la fonction
    }

    // Stocke temporairement l'index et la scène actuelle
    int index = manager->index;
    Scene_t *scene = manager->scenes[index];

    // Décharge la scène actuelle si elle a une fonction `unLoad`
    if (scene && scene->unLoad) { 
        scene->unLoad(scene);
    }

    // Met à jour l'index vers la nouvelle scène
    manager->index = newIndex;
    index = newIndex;
    scene = manager->scenes[index];

    // Charge la nouvelle scène si elle a une fonction `load`
    if (scene && scene->load) {
        scene->load(scene);
    }

    // Réinitialise `nextScene`
    strcpy(manager->nextScene, "");

    printf("[INFO] : Changement de scène réussi: nouvelle scène = %s\n", newScene);
}


/**
 * Joue la scene actuelle en faisant appel a chacune des methodes. 
 * A la fin du rendu effectue le changement de scene si une scene est en attente (variable char * nextScene).
 * Renvoi 1 par défaut, 0 si la fin du jeu a été déclenché. 
 */
int play_scene (SceneManager_t * manager, SDL_Event * event) {
    int continuePlay = TRUE ;
    int currentIndex = manager->index ;
    Scene_t * currentScene = manager->scenes[currentIndex] ;

    if (!currentScene->handleEvents(currentScene, event)) 
        continuePlay = FALSE ;

    if (!currentScene->update(currentScene))
        continuePlay = FALSE ;

    if (!currentScene->render(currentScene))
        continuePlay = FALSE ;


    if (strcmp(manager->nextScene, "") != 0) {
        change_scene(manager);
    }
    if (continuePlay == FALSE) {
        currentScene->unLoad(currentScene);
    } 

    return continuePlay ;
}


// ##########################################################################################
// ############################## ANCIENNES FONCTIONS DE SCENE ##############################
// ##########################################################################################


// void init_scene0(Camera_t * camera, Player_t * player, Map_t * map) {
//     init_elements_scene0(map);
    
// }


// void init_scene(Camera_t * camera, Player_t * player, Map_t * map) {
//     switch (gameStatus.scene) {
//         case 0 : 
//             init_scene0(camera, player, map) ;
//             break;
//         case 1 : 
//             init_scene0(camera, player, map) ;
//         default : 
//             break;
//     }
// }


// int play_scene0 (Camera_t * camera, Player_t * player, Map_t * map) {
//     SDL_Event event ;
//     uint32_t buttonClicked = FALSE;
//     uint8_t clicks = 0;
//     while (SDL_PollEvent(&event)) {
//         switch (event.type) {
//             case SDL_QUIT : 
//                 gameStatus.running = FALSE;
//                 break;
//             case SDL_KEYDOWN :
//                 switch (event.key.keysym.sym) {
//                     case SDLK_q :
//                         break;
//                     case SDLK_d :
//                         break;
//                     case SDLK_SPACE :
//                         break;
//                     case SDLK_BACKSPACE : 
//                         gameStatus.running = FALSE;
//                     default :
//                         break;
//                 }
//                 break;
//             case SDL_MOUSEBUTTONDOWN :
//                 printf("Bouton presser\n");
//                 element_update(map, &event);
//                 buttonClicked = 1;
//                 clicks = event.button.clicks;
//                 break;
//             case SDL_MOUSEBUTTONUP :
//                 printf("Bouton lever\n");
//                 element_update(map, &event);
//                 break;
//             case SDL_MOUSEMOTION : 
//                 move_element(map, &event);
//                 break;
//             default : 
//                 break;
//         }
//     }
     
//     // Effacer l'écran
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//     SDL_RenderClear (renderer); 

//     // position carre vert 
//     int cubeSize = 150;
//     SDL_Rect rect = {(camera->width / 2) - (cubeSize / 2), (camera->height / 2) - (cubeSize / 2), cubeSize, cubeSize};
    
//     // affiche carre vert en fonction de la position du curseur 
//     SDL_Point mouse ;
//     SDL_GetMouseState(&mouse.x, &mouse.y);
//     if (SDL_PointInRect(&mouse, &rect)) {
//         SDL_SetRenderDrawColor(renderer, 0, 200, 0, SDL_ALPHA_OPAQUE);
//         SDL_RenderFillRect(renderer, &rect);
        
//         // si boutton clicker sur carre vert change scene 
//         if (buttonClicked && clicks == 2) gameStatus.scene = 1;
//     }
//     else {
//         SDL_SetRenderDrawColor(renderer, 0, 100, 0, SDL_ALPHA_OPAQUE);
//         SDL_RenderFillRect(renderer, &rect);
//     }
    
    
//     // affiche le background test 
//     draw(camera, player, map);
    
//     // check la collision entre les element du bureau 
//     // check_elements_collision(map);
    
//     // Mettre à jour l'écran
//     SDL_RenderPresent (renderer);

//     // update position camera, se positionne sur un des 4 coins 
//     update_camera_random(camera);

//     // recupere les touche presser 
//     const uint8_t * keys = SDL_GetKeyboardState(NULL);
//     if (keys[SDL_SCANCODE_SPACE]) {
//         gameStatus.scene = 1;
//     }

//     return 0;
// }


// int play_scene1 (Camera_t * camera, Player_t * player, Map_t * map) {

//     SDL_Event event ;
//     uint32_t buttonClicked = FALSE;
//     while (SDL_PollEvent(&event)) {
//         switch (event.type) {
//             case SDL_QUIT : 
//                 gameStatus.running = FALSE;
//                 break;
//             case SDL_KEYDOWN :
//                 switch (event.key.keysym.sym) {
//                     case SDLK_q :
//                         break;
//                     case SDLK_d :
//                         break;
//                     case SDLK_SPACE :
//                         break;
//                     case SDLK_BACKSPACE : 
//                         gameStatus.running = FALSE;
//                         break;
//                     case SDLK_f :
//                         camera->followPlayer = (camera->followPlayer + 1) % 2; printf("changement follow\n");
//                         break;
//                     case SDLK_i :
//                         printf("INFO :\nplayer x, y, vx, vy : %f %f %f %f\ncamera x, y : %f %f\n", player->body.position.x, player->body.position.y, player->body.vx, player->body.vy, camera->x, camera->y);
//                         break;
//                     default :
//                         break;
//                 }
//                 break;
//             case SDL_MOUSEBUTTONDOWN :
//                 buttonClicked = SDL_MOUSEBUTTONDOWN;
//                 break;
//             case SDL_MOUSEBUTTONUP :
//                 buttonClicked = SDL_MOUSEBUTTONUP;
//                 break;
//         }
//     }

//     const uint8_t * keys = SDL_GetKeyboardState(NULL);
//     handle_input(keys, player);

//     // Effacer l'écran
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//     SDL_RenderClear (renderer); 

//     // met a jour la position des objets dynamique 
//     update_player(player, &map->ground);
//     update_camera(camera, player);

//     // dessine le rendu 
//     if (draw (camera, player, map)) {
//         gameStatus.running = 0;
//     }

//     // Mettre à jour l'écran
//     SDL_RenderPresent (renderer);

//     gameStatus.updateCount++;

//     if (gameStatus.updateCount == 5) {
//         gameStatus.updateCount = 0;
//         update_player_anim_state (player);
//     }     
    
//     return 0;
// }