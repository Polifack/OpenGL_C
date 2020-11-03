#include "transform.h"
#include "gameobject.h"
#include "vector3.h"
#include <GL/gl.h>


gameobject createGameobject(v3 pos, v3 scl, v3 rot, drawFunction draw){
    gameobject go;

    // Set the values to assigned
    go.transform.position = pos;
    go.transform.scale = scl;
    go.transform.eulerAngles = rot;

    // Set default values
    go.transform.anchorPoint = pos;
    go.transform.rotation = v3New(0, 0, 0);
    
    go.draw = draw;

    return go;
}

void renderGameobject(gameobject go){
    glPushMatrix();
    go.draw();          
    glPopMatrix();
}