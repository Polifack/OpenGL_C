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
#include "body.h"

#define W 720
#define H 720
#define ORIGIN_X 50
#define ORIGIN_Y 50

float aspectRatio;

v3 oldMousePosition;
v3 cameraRotation;

gameobject body;

arm arm_1;
arm arm_2;
arm arm_3;
arm arm_4;
arm arm_5;
arm arm_6;

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

void doRenders(){
    glLoadIdentity();       
    rotate(cameraRotation);

    renderGameobject(body);
    
    arm_1 = renderAtraction(arm_1);
    arm_2 = renderAtraction(arm_2);
    arm_3 = renderAtraction(arm_3);
    arm_4 = renderAtraction(arm_4);
    arm_5 = renderAtraction(arm_5);
    arm_6 = renderAtraction(arm_6);

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

    glClearColor(0.0,0.0,0.0,0.0);                  // Set black to background color

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