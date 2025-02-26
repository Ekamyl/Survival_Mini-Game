#pragma once 


typedef struct Rectangle_u {
    float x, y;
    float width, height;
} Rectangle_t ;

typedef struct RigidBody_u {
    Rectangle_t rec;
    SDL_Texture * texture;
    float vx, vy;           // velocité 
    float jump;             // valeur de saut 
    int onGround;           // si au sol  
} RigidBody_t ;

typedef struct StaticBody_u {
    Rectangle_t rec; 
    SDL_Texture * texture;
} StaticBody_t ;


void update_position (RigidBody_t * body);
int check_collision (Rectangle_t * a, Rectangle_t * b);
void ground_collision (RigidBody_t * object, Rectangle_t * ground);