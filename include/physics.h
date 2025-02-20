#pragma once 


typedef struct {
    float x, y;
    float width, height;
} Rectangle_t ;

typedef struct {
    Rectangle_t rec;
    float vx, vy;           // velocité 
    float jump;             // valeur de saut 
    int onGround;           // si au sol  
} RigidBody_t ;

typedef struct {
    Rectangle_t rec;
} StaticBody_t ;


void update_position (RigidBody_t * body);
int check_collision (Rectangle_t * a, Rectangle_t * b);
void ground_collision (RigidBody_t * object, StaticBody_t * ground);