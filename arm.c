#include "arm.h"
#include <GL/gl.h>
#include <GL/glut.h>

void drawLongPart(){
    glPushMatrix();                 // Save the matrix with the rotation 
        scale(v3New(1,5,1));
        setColor(v3New(0.6,0.2,0.6));
        glutSolidCube(1);       
        setColor(v3New(0, 0, 0));
        glutWireCube(1);        
    glPopMatrix();           
}
void drawWagonPart(){
    glPushMatrix();
        move(v3New(0, 3, 0));          
        scale(v3New(2,2,2));
        setColor(v3New(0.2, 0.6, 0.6));
        glutSolidCube(1);
        setColor(v3New(0, 0, 0));
        glutWireCube(1);
    glPopMatrix();
}

void armDrawFunction(){
    // Draw function runs after applying the transformations
    
    move(v3New(0, 3, 0));           // Move the whole arm 3 units (half the arm)
    
    drawLongPart();
    drawWagonPart();
}

gameobject createArmGameobject(float angleH, float angleV){
    v3 p = v3New(0, 2.5, 0);
    v3 s = v3New(1, 1, 1);
    v3 r = v3New(0, 0, 90);

    gameobject go = createGameobject(p, s, r, armDrawFunction);
    go.transform.rotation =  v3New(angleH, 0, angleV);

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

arm computeArmRotation(arm a, v3 position){
    transform t = a.gameobject.transform;
    float sidespeed = a.sidespeed;

    if (t.rotation.z > a.uplimit || t.rotation.z < a.dwlimit){
        a.upspeed = a.upspeed*-1;
    }
    
    a.gameobject.transform=doRotateArround(t, position, v3New(sidespeed, 0, a.upspeed));
    return a;
}