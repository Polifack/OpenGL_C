#include "body.h"
#include "gameobject.h"
#include "glaux.h"
#include "vector3.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>

void bodyDrawFunction(){
    //base 
    glPushMatrix();
        setColor(v3New(0.5,0.5,0.5));
        scale(v3New(5, 0.1, 5));
        glutSolidCube(1);
    glPopMatrix();
    
    // triangles
    glPushMatrix();
        move(v3New(0, 0, 1));
        rotate(v3New(270,0,0));
        setColor(v3New(0.8,0.2,0.2));
        scale(v3New(1,0.1,1));
        glutSolidCone(2, 5, 20, 20);
        setColor(v3New(0,0,0));
    glPopMatrix();

    glPushMatrix();
        move(v3New(0, 0, -1));
        rotate(v3New(270,0,0));
        setColor(v3New(0.8,0.2,0.2));
        scale(v3New(1,0.1,1));
        glutSolidCone(2, 5, 20, 20);
        setColor(v3New(0,0,0));
    glPopMatrix();

    
    // circles
    glPushMatrix();
        move(v3New(0,3.5,1));
        rotate(v3New(0, 0, 0));
        setColor(v3New(0.5,0.6,0));
        scale(v3New(1,1,0));
        glutWireSphere(3, 20, 2);
    glPopMatrix();

    glPushMatrix();
        move(v3New(0,3.5,-1));
        rotate(v3New(0, 0, 0));
        setColor(v3New(0.5,0.6,0));
        scale(v3New(1,1,0));
        glutWireSphere(3, 20, 2);
    glPopMatrix();
    
}

gameobject createBody(){
    v3 position = v3New(0, 0, 0);
    v3 scale = v3New(1, 1, 1);
    v3 rotation = v3New(0, 0, 0);
    gameobject go = createGameobject(position, scale, rotation, bodyDrawFunction);
    return go;
}