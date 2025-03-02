#pragma once 

#include "lib.h"

#define MAX_SCENES 2

extern SDL_Renderer * renderer ;
extern GameStatus_t gameStatus ;

typedef struct Camera_u Camera_t ;
typedef struct Player_u Player_t ;
typedef struct Map_u Map_t ; 
typedef struct Desktop_u Desktop_t ;
typedef struct DesktopElement_u DesktopElement_t ;

typedef struct Scene_u {
    char * name ;
    void ** data ;

    int (*load) (Scene_t *, void **) ;
    int (*unLoad) (Scene_t *, void **) ;

    int (*handleEvents) (Scene_t *, void **, SDL_Event *) ;
    int (*update) (Scene_t *, void **) ;
    int (*render) (Scene_t *, void **) ;
} Scene_t ;

typedef struct SceneManager_u {
    Scene_t scenes[MAX_SCENES] ;      // liste de scenes 
    int index ;             // indice de la scene active 
    char * nextScene ;      // nom de la prochaine, prends une valeur que si un changement de scene doit se produire 
} SceneManager_t ;


void init_scene(Camera_t * camera, Player_t * player, Map_t * map);
int play_scene0 (Camera_t *, Player_t *, Map_t *);
int play_scene1 (Camera_t *, Player_t *, Map_t *);


// A FAIRE ... 
void changeScene (SceneManager_t * game, char * newScene);
void pushScene (SceneManager_t * manager, Scene_t * newScene) ;
void RequestSceneChange (SceneManager_t * manager, char * name) ;

int playScene (SceneManager_t * manager, SDL_Event * event);

Scene_t * create_scene (char * name, int (*load) (Scene_t *, void **), int (*unLoad) (Scene_t *, void **), 
                        int (*handleEvents) (Scene_t *, void **), int (*update) (Scene_t *, void **), 
                        int (*render) (Scene_t *, void **));
void destroy_scene (Scene_t ** scene);

