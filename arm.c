#include "arm.h"
#include "glaux.h"
#include "vector3.h"
#include <GL/gl.h>
#include <GL/glut.h>

void renderBox(){
    glPushMatrix();
        move(v3New(3, 0, 0));          
        scale(v3New(1,1,2));
        glutSolidCube(1);
        setColor(v3New(0, 0, 0));
        glutWireCube(1);
    glPopMatrix();
}
void armDrawFunction(){      

    renderBox();
}

gameobject createArmGameobject(float startAngle){
    v3 p = v3New(0, 4, 0);    // Position where the arms are
    v3 s = v3New(1, 1, 1);    // Initial Scale
    v3 r = v3New(0, 0, 0);   // Initial Rotation (90deg)

    gameobject go = createGameobject(p, s, r, armDrawFunction);
    go.transform.rotation = v3New(0, 0, startAngle);

    return go;
}

arm armNew(float speed, float initAngle, v3 color){
    arm temp;
    temp.gameobject = createArmGameobject(initAngle);
    temp.speed=speed;
    temp.color=color;

    return temp;
}

arm renderAtraction(arm a){
    // Save the matrix before the render
    glPushMatrix();

    // Do all the transformations in order to put the arm in its place
    move(a.gameobject.transform.position);
    rotate(a.gameobject.transform.eulerAngles);
    
    // Update the rotation up or down
    transform t = a.gameobject.transform;

    // Do the rotation arround the center and up/down
    v3 anchorPoint=a.gameobject.transform.anchorPoint;
    v3 deltaRotation=v3New(0, 0, a.speed);
    
    t.anchorPoint = anchorPoint;     
    t.rotation = v3Sum(t.rotation, deltaRotation);
    rotateArround(t.position, t.anchorPoint, t.rotation);

    // Undo the rotation to make it paralel to the ground
    // v3 fixangle = v3New(0, 0, -t.rotation.z);
    // rotate(v3New(0, 0, -t.rotation.z));
    

    // Set color and Render box
    setColor(a.color);
    renderBox();

    // Restore the matrix
    glPopMatrix();
    
    // Save the transform modifications
    a.gameobject.transform=t;
    return a;
}