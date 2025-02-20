#include "../include/lib.h"
#include "../include/main.h"
#include "../include/player.h"
#include "../include/camera.h"
#include "../include/map.h"


Camera_t * camera_constructor (Player_t * player) {
    Camera_t * cam = malloc (sizeof(Camera_t));
    if (cam == NULL) {
        printf("Erreur malloc camera : %s\n", SDL_GetError());
        return NULL;
    }

    cam->x = player->body.rec.x + (player->body.rec.width / 2) - (CAMERA_WIDTH / 2);
    cam->y = BACKGROUND_HEIGHT - CAMERA_HEIGHT;
    cam->width = CAMERA_WIDTH;
    cam->height = CAMERA_HEIGHT;
    cam->deadzone = player->body.rec.width * 1.5;

    return cam;
}


void camera_destructor (Camera_t ** camera) {
    free(*camera);
    *camera = NULL;
}


void update_camera (Camera_t * camera, Player_t * player) {
    camera->x = player->body.rec.x + (player->body.rec.width / 2) - (CAMERA_WIDTH / 2); 
    camera->y = BACKGROUND_HEIGHT - CAMERA_HEIGHT;
    
    if (camera->x < 0) camera->x = 0;
    if ((camera->x + camera->width) > BACKGROUND_WIDTH) camera->x = BACKGROUND_WIDTH - camera->width;
}