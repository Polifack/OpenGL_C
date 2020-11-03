#include "body.h"
#include "gameobject.h"
#include <GL/glut.h>

void bodyDrawFunction(){
    // triangle
    glPushMatrix();
        rotate(v3New(270,0,0));
        setColor(v3New(0.8,0.2,0.2));
        glutSolidCone(1, 5, 20, 20);
        setColor(v3New(0,0,0));
        glutWireCone(1, 5, 20, 20);
    glPopMatrix();
    
    // base
    glPushMatrix();
        setColor(v3New(0.5,0.5,0.5));
        scale(v3New(5, 0.1, 5));
        glutSolidCube(1);
    glPopMatrix();
    
}

gameobject createBody(){
    v3 position = v3New(0, 0, 0);
    v3 scale = v3New(1, 1, 1);
    v3 rotation = v3New(0, 0, 0);
    gameobject go = createGameobject(position, scale, rotation, bodyDrawFunction);
    return go;
}