#include "arm.h"
#include "glaux.h"
#include "vector3.h"
#include <GL/gl.h>
#include <GL/glut.h>

void renderArm(){
    move(v3New(3, 0, 0));           
    // Render the long part
    glPushMatrix();
        scale(v3New(5,0.5,0.5));
        setColor(v3New(0.6,0.2,0.6));
        glutSolidCube(1);       
        setColor(v3New(0, 0, 0));
        glutWireCube(1);        
    glPopMatrix();     
}
void renderBox(){
    glPushMatrix();
        move(v3New(3, 0, 0));          
        scale(v3New(2,2,2));
        setColor(v3New(0.2, 0.6, 0.6));
        glutSolidCube(1);
        setColor(v3New(0, 0, 0));
        glutWireCube(1);
    glPopMatrix();
}
void armDrawFunction(){      
    renderArm();
    renderBox();
}

gameobject createArmGameobject(float angleH, float angleV){
    v3 p = v3New(0, 4, 0);    // Position where the arms are
    v3 s = v3New(1, 1, 1);    // Initial Scale
    v3 r = v3New(0, 0, 0);   // Initial Rotation (90deg)

    gameobject go = createGameobject(p, s, r, armDrawFunction);
    go.transform.rotation = v3New(0, angleH, angleV);

    return go;
}

arm armNew(float hSpeed, float vSpeed, float uLimit, float dLimit, float startAngleH, float startAngleV){
    arm temp;
    temp.gameobject = createArmGameobject(startAngleH, startAngleV);
    temp.sidespeed=hSpeed;
    temp.upspeed=vSpeed;
    temp.uplimit=uLimit;
    temp.dwlimit=dLimit;

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
    float sidespeed = a.sidespeed;
    if (t.rotation.z > a.uplimit || t.rotation.z < a.dwlimit){
        a.upspeed = a.upspeed*-1;
    }
    
    // Do the rotation arround the center and up/down
    v3 anchorPoint=a.gameobject.transform.anchorPoint;
    v3 deltaRotation=v3New(0, sidespeed, a.upspeed);
    
    t.anchorPoint = anchorPoint;     
    t.rotation = v3Sum(t.rotation, deltaRotation);
    rotateArround(t.position, t.anchorPoint, t.rotation);
    
    
    // Render the arm
    renderArm();

    // Undo the rotation    
    v3 fixangle = v3New(0, 0, -t.rotation.z);
    rotate(fixangle);

    // Change the position to be according to the movement of the arm
    v3 fixmov = v3New(0, t.rotation.z/a.uplimit, 0);
    move (fixmov);

    // Render box
    renderBox();

    // Restore the matrix
    glPopMatrix();
    
    // Save the transform modifications
    a.gameobject.transform=t;
    return a;
}