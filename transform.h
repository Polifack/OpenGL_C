#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include "vector3.h"
#include "glaux.h"

// Structure to store data about a object
typedef struct _transform{
    v3 position;            // v3 position in 3d space
    v3 scale;               // v3 that indicates the scaling in each angle
    v3 eulerAngles;         // v3 that indicates the rotation arround the center

    v3 anchorPoint;         // v3 that indicates the rotation point
    v3 rotation;            // v3 that indicates the rotation arround the anchor
} transform;

// Functions to delta modify parts of the transform
transform doRotation(transform t, v3 deltaRotation);
transform doTranslation(transform t, v3 deltaPosition);
transform doScaling(transform t, v3 deltaScale);

#endif