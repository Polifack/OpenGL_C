#ifndef GLAUX_H_INCLUDED
#define GLAUX_H_INCLUDED

#include <GL/gl.h>
#include "vector3.h"

// Auxiliar functions to do translations in 3d space
void moveX(float d);
void moveY(float d);
void moveZ(float d);
void move(v3 v);

// Auxiliar functions to do scaling in 3d space
void scaleX(float d);
void scaleY(float d);
void scaleZ(float d);
void scale(v3 v);

// Auxiliar functions to do rotations in 3d space
void rotateX(float a);
void rotateY(float a);
void rotateZ(float a);
void rotate(v3 v);

// Auxiliar functions to rotate arround something
void rotateArround(v3 currentPosition, v3 point, v3 angle);

// Auxiliar color functions
void setColor(v3 v);
v3 getRandomColor();

#endif