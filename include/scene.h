#pragma once 

#include "lib.h"

#define MAX_SCENES 2
#define NB_ELEM_DESKTOP_SCENE 4

extern SDL_Renderer * renderer ;
extern GameStatus_t gameStatus ;

typedef struct Camera_u Camera_t ;
typedef struct Player_u Player_t ;
typedef struct Map_u Map_t ; 
typedef struct Scene_u Scene_t ;

typedef struct Scene_u {
    char * name ;
    void ** data ;

    int (*load) (Scene_t *) ;
    int (*unLoad) (Scene_t *) ;

    int (*handleEvents) (Scene_t *, SDL_Event *) ;
    int (*update) (Scene_t *) ;
    int (*render) (Scene_t *) ;
} Scene_t ;

typedef struct SceneManager_u {
    Scene_t * scenes[MAX_SCENES] ;      // liste de scenes 
    int sceneCount ;        // nombre de scenes présentes dans la liste de scenes 
    int index ;             // indice de la scene active 
    char nextScene[128] ;      // nom de la prochaine, prends une valeur que si un changement de scene doit se produire 
} SceneManager_t ;


// fonctions manip scene manager et scene 
void change_scene (SceneManager_t * manager);
void push_scene (SceneManager_t * manager, Scene_t * newScene) ;
void request_scene_change (SceneManager_t * manager, char * name) ;
SceneManager_t * create_scene_manager () ;
void destroy_scene_manager (SceneManager_t ** manager) ;
int play_scene (SceneManager_t * manager, SDL_Event * event);
Scene_t * create_scene (char * name, int (*load) (Scene_t *), int (*unLoad) (Scene_t *), 
                        int (*handleEvents) (Scene_t *, SDL_Event *), int (*update) (Scene_t *), 
                        int (*render) (Scene_t *));
void destroy_scene (Scene_t ** scene);


// fonctions manip scene desktop
int DESKTOP_load (Scene_t * self) ;
int DESKTOP_unLoad (Scene_t * self) ;
int DESKTOP_handleEvents (Scene_t * self, SDL_Event * event) ;
int DESKTOP_update (Scene_t * self) ;
int DESKTOP_render (Scene_t * self) ; 

// fonctions manip scene level1
int LEVEL1_load (Scene_t * self) ;
int LEVEL1_unLoad (Scene_t * self) ;
int LEVEL1_handleEvents (Scene_t * self, SDL_Event * event) ;
int LEVEL1_update (Scene_t * self) ;
int LEVEL1_render (Scene_t * self) ; 