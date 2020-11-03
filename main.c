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

int cameraMode   = 0; // 0-> xaxis, 1-> yaxis
int cameraMoving = 0;

int isPerspective= 0; // 0-> ortho, 1-> persp

float initialSpeed = 1;
float rotationSpeed= 0;

v3 oldMousePosition;
v3 cameraRotation;

gameobject cuerpo_noria;
arm brazo_noria_0;
arm brazo_noria_1;
arm brazo_noria_2;
arm brazo_noria_3;
arm brazo_noria_4;
arm brazo_noria_5;

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);                              
    glLoadIdentity();                            
    aspectRatio = (GLfloat) w / (GLfloat) h;

    if (isPerspective)
        gluPerspective(90, aspectRatio, 1, 20);
    else
        glOrtho(-15 * aspectRatio, 15 * aspectRatio, -15, 15, -20.0, 20.0);
    
    glMatrixMode(GL_MODELVIEW);                               
}

void updateRotation(float speed){
    brazo_noria_0.speed=speed;
    brazo_noria_1.speed=speed;
    brazo_noria_2.speed=speed;
    brazo_noria_3.speed=speed;
    brazo_noria_4.speed=speed;
    brazo_noria_5.speed=speed;
}


void mousePositionHandler(int x, int y){
    float dx = oldMousePosition.x - x;
    float dy = oldMousePosition.y - y;

    if (cameraMode)
        cameraRotation.x += dy;
    else
        cameraRotation.y += dx;
    
    oldMousePosition.x = x;
    oldMousePosition.y = y;
}

void mouseClickHandler(int btn, int state, int x, int y){
    // Called whenever a mouse btn is 
    cameraMoving = (btn == 0 && state==0);
    printf("%d: %d,%d\n",glutGetModifiers(),x,y);
    if (glutGetModifiers() == GLUT_ACTIVE_SHIFT){
        cameraMode=1;
    }
    else{
        cameraMode=0;
    }
}

void keyboardHandler(unsigned char key, int x, int y ){
    printf("key: %d\n",key);

    switch(key){
        case 'P':
        case 'p': 
            printf("Setting perspective \n");
            isPerspective=1;
            reshape(W,H);
            break;
        case 'Q':
        case 'q': 
            printf("Setting orthog \n");
            isPerspective=0; 
            reshape(W,H); 
            break;
        case 'R': 
        case 'r':
            rotationSpeed = rotationSpeed*-1;
            updateRotation(rotationSpeed);
            break;
        case 'S':
        case 's': 
            if (rotationSpeed==0){
                rotationSpeed = initialSpeed;
                updateRotation(initialSpeed);
            }
            else{
                initialSpeed=rotationSpeed;
                rotationSpeed = 0;
                updateRotation(rotationSpeed);
            }
            break;
    }
}

void changeColors(v3 c){
    brazo_noria_0.color=c;
    brazo_noria_1.color=c;
    brazo_noria_2.color=c;
    brazo_noria_3.color=c;
    brazo_noria_4.color=c;
    brazo_noria_5.color=c;
}

void speedMenu(int s){
    if (rotationSpeed==0) return;
    if (rotationSpeed<1) s = s*-1;
    rotationSpeed = s;
    updateRotation(rotationSpeed);
}
void colorMenu(int value){
    switch (value) {
        case 1: 
            changeColors(v3New(1,0.3,0.3));
            break;
        case 2: 
            changeColors(v3New(0.3,0.3,1));
            break;
        case 3: 
            changeColors(v3New(0.3,1,0.3));
            break;
        case 4: 
            changeColors(v3New(1,0.3,0.6));
            break;
    }
}
void mainMenu(int id){
    switch( id){
        case 1:exit(1);break;
    }

    glutPostRedisplay();
}
void renderMenu(){
    int speedSubMenu = glutCreateMenu(speedMenu);
    glutAddMenuEntry("1", 1);
    glutAddMenuEntry("2", 2);
    glutAddMenuEntry("3", 3);

    int colorSubMenu = glutCreateMenu(colorMenu);
    glutAddMenuEntry("Red",1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Pink", 4);
//    glutAddMenuEntry("Rainbow", -1);

    glutCreateMenu(mainMenu);
    glutAddSubMenu("Rotation Speed", speedSubMenu);
    glutAddSubMenu("Change Color", colorSubMenu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutPostRedisplay();
}


void doRenders(){
    glLoadIdentity();       
    glTranslatef(0.0f, 0.0f, -10.0f);
    rotate(cameraRotation);
    
    renderGameobject(cuerpo_noria);
    brazo_noria_0 = renderAtraction(brazo_noria_0);
    brazo_noria_1 = renderAtraction(brazo_noria_1);
    brazo_noria_2 = renderAtraction(brazo_noria_2);
    brazo_noria_3 = renderAtraction(brazo_noria_3);
    brazo_noria_4 = renderAtraction(brazo_noria_4);
    brazo_noria_5 = renderAtraction(brazo_noria_5);
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

void init() {

    glutKeyboardFunc(keyboardHandler);      
    glutMotionFunc(mousePositionHandler);   
    glutMouseFunc(mouseClickHandler);       

    glClearColor(0.0,0.0,0.0,0.0);          

    // Create objects
    glLoadIdentity();
    rotationSpeed = initialSpeed;
    cuerpo_noria = createBody();

    v3 def_color = v3New(0.3, 0.6, 0.8);

    brazo_noria_0=armNew(rotationSpeed, 0, def_color);
    brazo_noria_1=armNew(rotationSpeed, 60, def_color);
    brazo_noria_2=armNew(rotationSpeed, 120, def_color);
    brazo_noria_3=armNew(rotationSpeed, 180, def_color);
    brazo_noria_4=armNew(rotationSpeed, 240, def_color);
    brazo_noria_5=armNew(rotationSpeed, 300, def_color);


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
    renderMenu();
    glutMainLoop();                                             // Arrancar el bucle de OpenGL

    return 0;

}