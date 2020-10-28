#include "glaux.h"

// Auxiliar functions to do translations in 3d space
void moveX(float d){glTranslatef(d, 0, 0);}
void moveY(float d){glTranslatef(0, d, 0);}
void moveZ(float d){glTranslatef(0, 0, d);}
void move(v3 v) { glTranslatef(v.x, v.y, v.z);}

// Auxiliar functions to do scaling in 3d space
void scaleX(float d){glScalef(d, 1, 1);}
void scaleY(float d){glScalef(1, d, 1);}
void scaleZ(float d){glScalef(1, 1, d);}
void scale(v3 v){ glScalef(v.x, v.y, v.z);}

// Auxiliar functions to do rotations in 3d space
void rotateX(float a){ glRotatef(a, 1,0,0);}
void rotateY(float a){ glRotatef(a, 0,1,0);}
void rotateZ(float a){ glRotatef(a, 0,0,1);}
void rotate(v3 v){ rotateX(v.x); rotateY(v.y); rotateZ(v.z);}

// Auxiliar color functions
void setColor(v3 v){glColor3f(v.x, v.y, v.z);}

