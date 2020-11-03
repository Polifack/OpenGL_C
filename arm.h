#ifndef ARM_H_INCLUDED
#define ARM_H_INCLUDED

#include "gameobject.h"

typedef struct s_arm{
    gameobject gameobject;
    float speed;
    v3 color;
} arm;

arm armNew(float speed, float initialAngl, v3 color);
arm renderAtraction(arm a);

#endif