#include "transform.h"
#include "glaux.h"
#include "vector3.h"
#include <GL/gl.h>

void applyTransform(transform t){
    glLoadIdentity();
    
    move(t.position);
    
    rotate(t.eulerAngles);
    rotateArround(t.position, t.anchorPoint, t.rotation);

    scale(t.scale);
}


//// cada una de estas operaciones debe aplicar move scale rotate etc
//// y hay que borrar apply transform, porque no tenemos en cuenta el modo
//// en el que se hacen las transformaciones en opengl

// position -> posicion local
// euler -> angulos locales
// scale -> escala local


transform doRotation(transform t, v3 deltaRotation){
    v3 currentRotation = t.eulerAngles;
    v3 nextRotation = v3Sum(currentRotation, deltaRotation);

    t.eulerAngles = nextRotation;
    rotate(t.eulerAngles);
    
    return t; 
}

transform doTranslation(transform t, v3 deltaPosition){
    v3 currentPosition = t.position;
    v3 nextPosition = v3Sum(currentPosition, nextPosition);

    t.position = nextPosition;
    move(t.position);

    return t;
}

transform doScaling(transform t, v3 deltaScale){
    v3 currentScale = t.scale;
    v3 nextScale = v3Sum(currentScale, deltaScale);

    t.scale = nextScale;
    scale(t.scale);

    return t;
}

// Esta funcion no actualiza la posicion del transform
// Para que el valor de t.transform sea el correcto habria que hacer el calculo del angulo
// Hay que implementar las operaciones con coords homogeneas
transform doRotateArround(transform t, v3 rotationPoint, v3 deltaAngles){
    // Set the object "pivot" in the rotation point
    
    t.anchorPoint = rotationPoint;     
    t.rotation = v3Sum(t.rotation, deltaAngles);
    
    v3Print(t.rotation);
    
    return t;
}