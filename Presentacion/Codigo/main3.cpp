#include "Angel-yjc.h"
#include <iostream>
#include <fstream>
#include <string>

#include<stdlib.h>
#include <stdio.h>
#include<time.h>
#include <GL/glext.h>


using namespace std;

typedef Angel::vec3 point3;
typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

struct Particula {
public:
    point3 posicion;
    point3 direccion;
    point3 velocidad;    
    float edad = 0;
    float maxEdad = 0;
    float limite = 5;
    
    
    
    
    //possicion inicial
    //velocodad inicial(velocidad y direccion)
    //tamaño inicial
    //color inicial
    //transparencia inicial
    //forma
    //tiempo de vida

    Particula(GLfloat x, GLfloat y, GLfloat z, GLfloat dx, GLfloat dy, GLfloat dz, float maxEdad, float limite) {
        this->posicion.x = x;
        this->posicion.y = y;
        this->posicion.z = z;
        this->direccion.x = dx;
        this->direccion.y = dy;
        this->direccion.z = dz;
        this->maxEdad = maxEdad;
        this->limite = limite;
    }

    Particula() {
    }
};


GLuint program;
GLuint idAParticulas;
GLuint arrayObjetos;
const GLchar* feedbackVaryings[] = {"posicion", "direccion", "velocidad", "edad", "maxEdad", "limite"};
GLuint tbo;
GLuint tbo2;
GLuint query;

//const int cantParticulas = 1000 * 10*3;
const int cantParticulas = 1;
const int32_t maxParticulas = 100000 * 10;
int cantParticulasNuevas = cantParticulas;

Particula *particulas = new Particula[maxParticulas];
//Particula particulas[maxParticulas];

float xIniRam, yIniRam, zIniRam;
float xDirRam, yDirRam, zDirRam;
float maxEdadRandom, limiteRandom;
//float xIniRam, yIniRam, zIniRam;

void iniciarSistemaParticulas() {

    

    /*for (int i = 0; i < cantParticulas; i++) {
        num = (rand() % (2000)) / 10000.0f - 0.15;
        num2 = (rand() % (100)) / 10000.0f;
        num3 = (rand() % (2000)) / 10000.0f - 0.15;
        particulas[i] = Particula(num, num2, num3);
    }

    /*particulas[0] = Particula(-0.5, -0.5, 0);
    particulas[1] = Particula(-0.5,  0.5, 0);
    particulas[2] = Particula( 0.5,  0.5, 0);
    particulas[3] = Particula( 0.5, -0.5, 0);*/


    
}

clock_t t_ini, t_fin;
clock_t tiempoActual;
double secs;
void init(void) {

    glGenVertexArrays(1, &arrayObjetos);
    glBindVertexArray(arrayObjetos);

    srand(time(NULL));
    iniciarSistemaParticulas();
    
    glGenBuffers(1, &idAParticulas);
    glBindBuffer(GL_ARRAY_BUFFER, idAParticulas);
    glBufferData(GL_ARRAY_BUFFER, sizeof (Particula) * maxParticulas, particulas, GL_DYNAMIC_DRAW);
    cout << "si:" << sizeof (particulas) << endl;



    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof (Particula) * maxParticulas, nullptr, GL_DYNAMIC_READ);



    glGenQueries(1, &query);

    // Load shaders and create a shader program (to be used in display())
    //program = InitShader("Shaders/vsTF.glsl", "Shaders/fsTF.glsl");
    //program = InitShader("Shaders/vsTF.glsl", "Shaders/gsTF.glsl",  "Shaders/fsTF.glsl");
    program = InitShader("Shaders/vsTF.glsl", "Shaders/gsTF.glsl", "Shaders/fsTF.glsl", feedbackVaryings);

    t_ini = clock();
    
}

float color3 = 0.0;
float aumentoPosY = 0.0;
GLfloat aspect;
GLfloat anguloX = 0, anguloY = 0;
GLfloat fovy = 45.0;
GLfloat desplazoY = -0.5;

GLuint cantidadActual = cantParticulas;
bool usandoDataInicial = true;
int backActual = 100;
float maxVida = 1000;
int posi;
float limitePro=1;


void drawgraphix() {


    glEnable(GL_PROGRAM_POINT_SIZE);
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    t_fin = clock();
    secs = (double) (t_fin - t_ini) / CLOCKS_PER_SEC;
    secs *= 1000;
    glUniform1f(glGetUniformLocation(program, "deltaTime"),secs);
    t_ini = clock();
    
    //tiempoActual = clock();
    //glUniform1f(glGetUniformLocation(program, "tiempoActual"),secs);
    
    glUniform1f(glGetUniformLocation(program, "maxVida"),maxVida);
    glUniform1f(glGetUniformLocation(program, "limitePro"),limitePro);

    GLuint projection = glGetUniformLocation(program, "projection");
    //mat4 p = Perspective(fovy, aspect, 0.1f, 100.0f); //fovy, aspect, zNear, zFar
    mat4 p = Ortho(-fovy,fovy,-fovy,fovy,0.1,100);
    glUniformMatrix4fv(projection, 1, GL_TRUE, p);


    GLuint model_view = glGetUniformLocation(program, "model_view");
    vec4 eye(0.0, 0.0, -3.0, 1.0); // La posición de tu cámara en el espacio mundo
    vec4 at(0.0, 0.0, 0.0, 0.0); // Hacia donde quieres mirar, en el espacio mundo
    vec4 up(0.0, 1.0, 0.0, 0.0);
    mat4 mv = LookAt(eye, at, up);
    mv = mv * Translate(0, desplazoY, 0) * RotateY(anguloY) * RotateX(anguloX);
    glUniformMatrix4fv(model_view, 1, GL_TRUE, mv); // GL_TRUE: matrix is row-major

    glUseProgram(program);




    glBindBuffer(GL_ARRAY_BUFFER, idAParticulas);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (Particula), (void*) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof (Particula), (void*) (sizeof(point3)) );
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof (Particula), (void*) (sizeof(point3)*2) );
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof (Particula), (void*) (sizeof(point3)*3) );
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof (Particula), (void*) (sizeof(point3)*3+sizeof(float)) );
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof (Particula), (void*) (sizeof(point3)*3+sizeof(float)*2) );
    
    
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);


    glBindBuffer(GL_ARRAY_BUFFER, idAParticulas);

    glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query);
    glBeginTransformFeedback(GL_POINTS);

    glDrawArrays(GL_POINTS, 0, cantidadActual);

    //glDrawTransformFeedback(GL_POINTS, tbo);

    glEndTransformFeedback();
    glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
    //glFlush();


    glGetQueryObjectuiv(query, GL_QUERY_RESULT, &cantidadActual);

    Particula *feedback = new Particula[cantidadActual];

    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof (Particula) * cantidadActual, feedback);

    cout << "--------" << cantidadActual << endl;

    

    for (int i = 0; i < cantidadActual; i++) {
        particulas[i] = feedback[i];
        

    }

    int aux = cantidadActual + cantParticulasNuevas;
    if(aux>=maxParticulas)
        aux = maxParticulas-1;
    for (int i = cantidadActual; i < aux; i++) {
        xIniRam = (rand() % (2000)) / 10000.0f - 0.15;
        yIniRam = (rand() % (1000)) / 10000.0f;
        zIniRam = (rand() % (2000)) / 10000.0f - 0.15;
        
        xDirRam = (rand() % (1000)) / 1000.0f - 0.5;
        yDirRam = (rand() % (100)) / 1000.0f;
        zDirRam = (rand() % (1000)) / 1000.0f - 0.5;
        
        maxEdadRandom = rand() % ((int)maxVida) ;
        limiteRandom = (rand() % (300))/100 ;
        
        particulas[i] = Particula(xIniRam, yDirRam, zIniRam, xDirRam, yDirRam, zDirRam, maxEdadRandom, limiteRandom);
    }
    
    delete feedback;
    cantidadActual += cantParticulasNuevas;
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof (Particula) * maxParticulas, particulas);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
    glDisableVertexAttribArray(5);


    t_fin = clock();

    glutSwapBuffers();
    glutPostRedisplay();
}

void reshapefunc(int width, int height) {

    glViewport(0, 0, width, height);
    aspect = (GLfloat) width / (GLfloat) height;

    glutPostRedisplay();

}

void keyboardfunc(unsigned char key, int x, int y) {
    switch (key) {
        case 27: case 'q':
        {
            exit(0);
            break;
        }
        case 'a':
        {
            fovy += 1;
            break;
        }
        case 'd':
        {
            fovy -= 1;
            break;
        }

        case 'w':
        {
            desplazoY += 0.1;
            break;
        }
        case 's':
        {
            desplazoY -= 0.1;
            break;
        }
        case ' ':
        {
            anguloX = 0;
            anguloY = 0;
            fovy = 45.0;
            break;
        }
        case '+':
        {
            cantParticulasNuevas += 100;
            break;
        }
        case '-':
        {
            cantParticulasNuevas -= 100;
            break;
        }
        case 'x':
        {
            maxVida += 10;
            break;
        }
        case 'z':
        {
            maxVida -= 10;
            break;
        }
        case 'v':
        {
            limitePro += 0.2;
            break;
        }
        case 'c':
        {
            limitePro -= 0.2;
            break;
        }
    }
    glutPostRedisplay();

}

void specialKeyInput(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
        {
            anguloY += 2;
            break;
        }
        case GLUT_KEY_LEFT:
        {
            anguloY -= 2;
            break;
        }
        case GLUT_KEY_UP:
        {
            anguloX += 2;
            break;
        }
        case GLUT_KEY_DOWN:
        {
            anguloX -= 2;
            break;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(200, 100);
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
    glutSpecialFunc(specialKeyInput);

    glutMainLoop();

    return (0);
}