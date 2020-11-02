#ifndef ARM_H_INCLUDED
#define ARM_H_INCLUDED

#include "gameobject.h"

typedef struct s_arm{
    gameobject gameobject;
    float sidespeed;
    float upspeed;
    float uplimit;
    float dwlimit;
} arm;

arm armNew(float hSpeed, float vSpeed, float uLimit, float dLimit, float startAngleH, float startAngleV);
arm computeArmRotation(arm a, v3 position);

#endif