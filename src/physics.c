#include "../include/lib.h"
#include "../include/main.h"
#include "../include/physics.h"


// met a jour a position x et y en focntiond de la velocite 
void update_position (RigidBody_t * body) {
    body->rec.x += body->vx ; 
    body->rec.y += body->vy ; 
}

// renvoi 1 si a en colision avec b, 0 sinon
int check_collision(Rectangle_t * a, Rectangle_t * b) {
    return (a->x < b->x + b->width &&
            a->x + a->width > b->x &&
            a->y < b->y + b->height &&
            a->y + a->height > b->y);
}

// si l'objet est en collision avec le sol, met a jour ses coordonnes 
void ground_collision (RigidBody_t * object, StaticBody_t * ground) {
    if (check_collision(&object->rec, &ground->rec)) {
        object->rec.y = ground->rec.y - object->rec.width;
        object->vy = 0;
        object->onGround = TRUE;
    }
}