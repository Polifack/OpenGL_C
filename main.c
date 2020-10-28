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
#include "vector3.h"

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



// Program

float aspectRatio;
gameobject body;

void init() {
    glClearColor(0.0,0.0,0.0,0.0);                              // Set black to background color

    body = createBody();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Borrado del FrameBuffer
    glEnable(GL_DEPTH_TEST);

    renderGameobject(body);

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