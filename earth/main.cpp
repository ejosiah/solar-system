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

using namespace physics;
using namespace std;

float scale = 0.00078480615f;

float d = 15;
GLuint textureId;
sphere earth, clouds, moon;
float spin = 0;
float moonSpin = 0;
float moonOrbit = 0;
float speed = 6.0f; // float speed = 0.004166666666667f;
float orbitSpeed = speed/28;
float moonR = 1.363208287552974;
GLuint moonTexture;
GLuint cloudTexture;

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
    
    earth = {5, 20, 20, "/Users/jay/projects/earth/earthmap1k.jpg"};
    clouds = {5.2, 50, 50, {1.0, 1.0, 1.0, 0.3}, "/Users/jay/projects/earth/earthcloudmaptrans.jpg"};
    moon = {moonR, 50, 50, "/Users/jay/Downloads/moon.jpg"};
}

void updateRotation(){
    real sin0 = real_sin(spin/2 * DEG_TO_RAD);
    real cos0 = real_cos(spin/2 * DEG_TO_RAD);
    Vector rot = rotAxis * sin0;
    Quaternion q{ cos0, rot.x, rot.y, rot.z };
    q.normailize();
    Matrix4 m;
    m.rotate(q);
    
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){
            transformation[j * 4 + i] = m(i, j);
        }
    }
    
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();

    gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
    
    glPushMatrix();
    glRotated(moonOrbit, 0, 1, 0);
    glTranslatef(0, 0, d);
    glRotated(moonOrbit, 0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, moonTexture);
    moon.draw();
    glPopMatrix();
    
    glTranslatef(0, earth.r, 0);
    
    
    updateRotation();
    glPushMatrix();
    glTranslatef(0, -earth.r, 0);
    glRotatef(180, 1, 0, 0);
    glTranslatef(0, earth.r, 0);
    glMultMatrixf(transformation);
    glTranslatef(0, -earth.r, 0);
    
    
    earth.draw();
    
    glDepthMask(false);
    glRotatef(spin, 0, 1, 0);
    clouds.draw();
    glDepthMask(true);
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
}

void update(){
    float t = glutGet(GLUT_ELAPSED_TIME)/1000.0f;
    spin = speed * t;
    moonOrbit = orbitSpeed * t;
    if(spin > 360) spin -= 360;
    if(moonOrbit > 360) moonOrbit -= 360;
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
    
    
    init();
    
    glutMainLoop();
    
    return 0;
}
