#include <GL/freeglut_std.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string.h>
#include <GL/glut.h>
#include "gameobject.h"
#include "glaux.h"
#include "transform.h"
#include "vector3.h"
#include "arm.h"

#define W 720
#define H 720
#define ORIGIN_X 50
#define ORIGIN_Y 50

// Rendering functions

void bodyDrawFunction(){
    // triangle
    
    glPushMatrix();
    rotate(v3New(270,0,0));
    setColor(v3New(0.8,0.2,0.2));
    glutSolidCone(1, 5, 20, 20);
    setColor(v3New(0,0,0));
    glutWireCone(1, 5, 20, 20);
    glPopMatrix();
    
    // base
    glPushMatrix();
    setColor(v3New(0.5,0.5,0.5));
    scale(v3New(5, 0.1, 5));
    glutSolidCube(1);
    glPopMatrix();
    
}


gameobject createBody(){
    v3 position = v3New(0, 0, 0);
    v3 scale = v3New(1, 1, 1);
    v3 rotation = v3New(0, 0, 0);
    gameobject go = createGameobject(position, scale, rotation, bodyDrawFunction);
    return go;
}
// Program

float aspectRatio;

v3 oldMousePosition;
v3 cameraRotation;

gameobject body;
gameobject center;

void mousePositionHandler(int x, int y){
    

    float dx = oldMousePosition.x - x;
    float dy = oldMousePosition.y - y;

    cameraRotation.x += dy ;
    cameraRotation.y += dx ;

    oldMousePosition.x = x;
    oldMousePosition.y = y;
}

void mouseClickHandler(int btn, int state, int x, int y){

}

void keyboardHandler(unsigned char key, int x, int y ){

}

arm arm_1;
arm arm_2;
arm arm_3;
arm arm_4;
arm arm_5;
arm arm_6;

arm moveAndRenderArm(arm a){
    glPushMatrix();

    // Do all the transformations in order to put the arm in its place
    move(a.gameobject.transform.position);
    rotate(a.gameobject.transform.eulerAngles);
    
    // Update the rotation
    a=computeArmRotation(a, center.transform.position);
    
    // Render the model
    renderGameobject(a.gameobject);
    
    glPopMatrix();
    return a;
}

void renderBody(){
    renderGameobject(body);
}

void doRenders(){
    glLoadIdentity();       
    rotate(cameraRotation);

    glPushMatrix();
        renderBody();
    glPopMatrix();
    
    arm_1 = moveAndRenderArm(arm_1);
    arm_2 = moveAndRenderArm(arm_2);
    arm_3 = moveAndRenderArm(arm_3);
    arm_4 = moveAndRenderArm(arm_4);
    arm_5 = moveAndRenderArm(arm_5);
    arm_6 = moveAndRenderArm(arm_6);

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Borrado del FrameBuffer
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();

    doRenders();

    glLoadIdentity();
    glutSwapBuffers();   
    
    glutPostRedisplay();                                      //force update
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);                              
    glLoadIdentity();                            
    aspectRatio = (GLfloat) w / (GLfloat) h;
    glOrtho(-15 * aspectRatio, 15 * aspectRatio, -15, 15, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);                               
}

void init() {

    glutKeyboardFunc(keyboardHandler);              // Link the handler to keyboard function
    glutPassiveMotionFunc(mousePositionHandler);    //
    glutMouseFunc(mouseClickHandler);               //

    glClearColor(0.0,0.0,0.0,0.0);                              // Set black to background color

    // Create objects
    glLoadIdentity();
    
    body = createBody();
    
    arm_1=armNew(1, 1, 30, -30, 0, 0);
    arm_2=armNew(1, 1, 30, -30, 60, 30);
    arm_3=armNew(1, 1, 30, -30, 120, 0);
    arm_4=armNew(1, 1, 30, -30, 180, 30);
    arm_5=armNew(1, 1, 30, -30, 240, 0);
    arm_6=armNew(1, 1, 30, -30, 300, 30);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                                      // Cargar el teclado y el ráton

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // Búffer doble, con color RGB y profundidad

    glutInitWindowSize(W, H);                                   // Tamaño de la ventana
    glutInitWindowPosition(ORIGIN_X, ORIGIN_Y);                 // Posición del extremo superior-izquierdo de la ventana

    glutCreateWindow("GLUT Articulado");                        // Crear la ventana
    init();
    glutDisplayFunc(display);                                   // Activar la función de pintado
    glutReshapeFunc(reshape);                                   // Activar la función de escalado

    glutMainLoop();                                             // Arrancar el bucle de OpenGL

    return 0;

}