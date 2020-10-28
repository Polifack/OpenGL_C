#include "transform.h"
#include "gameobject.h"

gameobject createGameobject(v3 pos, v3 scl, v3 rot, drawFunction draw){
    gameobject go;

    go.transform.position = pos;
    go.transform.scale = scl;
    go.transform.eulerAngles = rot;
    
    go.draw = draw;

    return go;
}

void renderGameobject(gameobject go){
    // en opengl todas las transformaciones se hacen sobre el eje
    // guardar la matriz de transformacion y luego recuperarla permite
    // que las transformaciones se hagan sobre objetos

    glPushMatrix();

    applyTransform(go.transform);
    go.draw();

    glPopMatrix();
}

gameobject goRotation(gameobject go, v3 delta){
    transform ct = go.transform;
    transform t = doRotation(ct, delta);
    go.transform = t;
    return go;
}

gameobject goTranslation(gameobject go, v3 delta){
    transform ct = go.transform;
    transform t = doTranslation(ct, delta);
    go.transform = t;
    return go;
}

gameobject goScaling(gameobject go, v3 delta){
    transform ct = go.transform;
    transform t = doScaling(ct, delta);
    go.transform = t;
    return go;
}