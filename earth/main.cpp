//
//  main.cpp
//  earth
//
//  Created by Josiah Ebhomenye on 19/12/2016.
//  Copyright © 2016 Josiah Ebhomenye. All rights reserved.
//

#include <iostream>

#include <gl/glew.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <soil/SOIL.h>

#include <maths/vector.h>
#include <maths/Matrix4.h>
#include <maths/Quaternion.h>
#include "sphere.h"
#include "earth.h"
#include "moon.h"

using namespace physics;
using namespace std;

float scale = 0.00078480615f;

float d = 15;
float speed = 6.0f * DEG_TO_RAD; // float speed = 0.004166666666667f;
//float speed = 10 * physics::PI;
float orbitSpeed = speed/28;
float moonR = 1.363208287552974;
Earth earth{speed};
Moon moon{moonR, d, orbitSpeed};
float currentTime = 0;


Vector rotAxis{-0.398894, 0.916997, 0};
real transformation[16];

void init(){
    glClearColor(0, 0, 0, 0);
    
    float light_pos[] = {0.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    earth.init();
    moon.init();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();

    gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
    
    moon.draw();
    earth.draw();
    
    
    glFlush();
    glutSwapBuffers();
}

float getElapsedTime(){
    float t = ((glutGet(GLUT_ELAPSED_TIME)/1000.0) - currentTime);
    currentTime += t;
    return t;
}

void update(){
    float t = getElapsedTime();
    earth.update(t);
    moon.update(t);
    glutPostRedisplay();
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, double(w)/h, 1, 200);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,  char * argv[]) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Earth");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(update);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    init();
    
    glutMainLoop();
    
    return 0;
}
