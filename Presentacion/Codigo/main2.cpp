/*#include "Angel-yjc.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

using namespace std;

typedef Angel::vec3 point3;
typedef Angel::vec4 color4;

static int winwidth, winheight;


GLuint program;
GLuint nombre_idb;
GLuint color_idb;

GLuint arrayObjetos;


// Projection transformation parameters
GLfloat  fovy = 45.0;  // Field-of-view in Y direction angle (in degrees)
GLfloat  aspect=1.0f;       // Viewport aspect ratio
//GLfloat  zNear = 0.5, zFar = 3.0;
GLfloat  zNear = 0.1, zFar = 100.0;

GLfloat angleX = 0.0; // rotation angle in degrees
GLfloat angleY = 0.0;
GLfloat angleZ = 0.0;
GLfloat angle = 0.0;
vec4 init_eye(0.0, 0.0, -2.0, 1.0); // initial viewer position
vec4 eye = init_eye;  

point3 nombre_buffer2[] = {
    point3(-1.0f, -1.0f, 0.0f), point3(1.0f, 0.0f, 0.0f),
    point3(1.0f, -1.0f, 0.0f), point3(0.0f, 1.0f, 0.0f),
    point3(0.0f, 1.0f, 0.0f), point3(0.0f, 0.0f, 1.0f)
};

point3 nombre_buffer[] = {
    point3(-1.0f, -1.0f, 0.0f),
    point3(1.0f, -1.0f, 0.0f),
    point3(0.0f, 1.0f, 0.0f)
};


point3 color_buffer[] = {
    point3(1.0f, 0.0f, 0.0f),
    point3(0.0f, 1.0f, 0.0f),
    point3(0.0f, 0.0f, 1.0f)
};


void init(void) {
    glGenVertexArrays(1, &arrayObjetos);
    glBindVertexArray(arrayObjetos);


    glGenBuffers(1, &nombre_idb);
    glBindBuffer(GL_ARRAY_BUFFER, nombre_idb);
    glBufferData(GL_ARRAY_BUFFER, sizeof (nombre_buffer), nombre_buffer, GL_STATIC_DRAW);

    glGenBuffers(1, &color_idb);
    glBindBuffer(GL_ARRAY_BUFFER, color_idb);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer), color_buffer, GL_STATIC_DRAW);

    // Load shaders and create a shader program (to be used in display())
    program = InitShader("Shaders/vs2.glsl", "Shaders/fs2.glsl");
}

void drawgraphix() {

    // Habilidad el test de profundidad
    glEnable(GL_DEPTH_TEST);
    // Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, nombre_idb);
    //location = 0, tam, tipo, f we want the data to be normalized, stride(tam en byte), offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_idb);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);


    glUseProgram(program);
    //glBindVertexArray(arrayObjetos);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //glDisableVertexAttribArray(0);
    //glDisableVertexAttribArray(1);

    glutSwapBuffers();
}

void reshapefunc(int width, int height) {
    winwidth = width;
    winheight = height;

    glViewport(0, 0, width, height);


}

void keyboardfunc(unsigned char key, int x, int y) {
    switch (key) {
        case 27: exit(0);
            break;
    }
}

int main(int argc, char **argv) {
    winwidth = 512;
    winheight = 512;

    glutInit(&argc, argv);
    glutInitWindowSize(winwidth, winheight);
    glutInitWindowPosition(500, 300);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Practica 1 - Ejercicio 1.1");

    int err = glewInit();
    if (GLEW_OK != err) {
        printf("Error: glewInit failed: %s\n", (char*) glewGetErrorString(err));
        exit(1);
    }

    init();

    glutDisplayFunc(drawgraphix);
    glutReshapeFunc(reshapefunc);
    glutKeyboardFunc(keyboardfunc);

    glutMainLoop();

    return (0);
}*/