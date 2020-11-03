#include "transform.h"
#include "glaux.h"
#include "vector3.h"
#include <GL/gl.h>

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