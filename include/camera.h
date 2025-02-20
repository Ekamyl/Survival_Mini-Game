#pragma once 

#include "window.h"

#define CAMERA_WIDTH 1080 
#define CAMERA_HEIGHT 720

typedef struct {
    float x, y;
    float width, height;
    float deadzone;
} Camera_t ;

typedef struct Player_u Player_t ;

void camera_destructor (Camera_t ** camera);
Camera_t * camera_constructor (Player_t * player);
void update_camera (Camera_t * camera, Player_t * player);