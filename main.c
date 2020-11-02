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
    glBegin(GL_TRIANGLES);                      
        setColor(v3New(0.5,0.5,0.5));

        glVertex3f( 0.0f, 1.0f, 0.25f);
        glVertex3f( 0.5f, 0.0f, 0.25f);
        glVertex3f(-0.5f, 0.0f, 0.25f);

        glVertex3f( 0.0f, 1.0f, -0.25f);
        glVertex3f( 0.5f, 0.0f, -0.25f);
        glVertex3f(-0.5f, 0.0f, -0.25f);

    glEnd();  // End of drawing color-cube

    glBegin(GL_POLYGON);                  
        setColor(v3New(1, 0.3, 0.3));
        // base
        glVertex3f( 0.5f, 0.0f,-0.25f);
        glVertex3f( 0.5f, 0.0f, 0.25f);
        glVertex3f(-0.5f, 0.0f, 0.25f);
        glVertex3f(-0.5f, 0.0f,-0.25f);

    glEnd();  

    glBegin(GL_POLYGON);                  
        setColor(v3New(0.3, 1, 0.3));
        // side1
        glVertex3f( 0.0f, 1.0f, 0.25f);
        glVertex3f(-0.5f, 0.0f, 0.25f);
        glVertex3f(-0.5f, 0.0f,-0.25f);
        glVertex3f( 0.0f, 1.0f,-0.25f);
    glEnd();  

    glBegin(GL_POLYGON);                  
        setColor(v3New(0.3, 0.3, 1));
        // side2
        glVertex3f( 0.0f, 1.0f,-0.25f);
        glVertex3f( 0.5f, 0.0f,-0.25f);
        glVertex3f( 0.5f, 0.0f, 0.25f);
        glVertex3f( 0.0f, 1.0f, 0.25f);
    glEnd();  
}




gameobject createBody(){
    v3 position = v3New(0, 0, 0);
    v3 scale = v3New(3.0f, 5.0f, 1.0f);
    v3 rotation = v3New(0, 0, 0);
    gameobject go = createGameobject(position, scale, rotation, bodyDrawFunction);
    return go;
}
void centerDrawFunction(){
    setColor(v3New(1,1,0));
    glutWireSphere(1, 20, 20);
}
gameobject createCenter(){
    v3 p = v3New(0, 2.5, 0);        // The arm should be in the center of the body
    v3 s = v3New(1, 1, 1);          // The arm should be the same size of the body
    v3 r = v3New(0, 0, 0);          

    gameobject go = createGameobject(p, s, r, centerDrawFunction);
    return go;
}

void cubeDrawFunction(){
    glutSolidCube(1);
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
    a=computeArmRotation(a, center.transform.position);
    renderGameobject(a.gameobject);
    glPopMatrix();
    return a;
}

void doRenders(){
    glLoadIdentity();       
    rotate(cameraRotation);

    glPushMatrix();
        renderGameobject(body);
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
    center = createCenter();
    
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