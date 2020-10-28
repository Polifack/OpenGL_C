#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "vector3.h"
#include "glaux.h"
#include "transform.h"

typedef void (*drawFunction)();
typedef struct _gameobject{
    transform transform;        // Scale, rotation and position
    drawFunction draw;          // Draw polygons function
} gameobject;

gameobject createGameobject(v3 pos, v3 scl, v3 rot, drawFunction draw);
void renderGameobject(gameobject go);

gameobject goRotation(gameobject go, v3 delta);
gameobject goTranslation(gameobject go, v3 delta);
gameobject goScaling(gameobject go, v3 delta);

#endif