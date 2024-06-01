#ifndef TUGAS_H
#define TUGAS_H
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Window dimensions
extern int windowWidth;
extern int windowHeight;

// Camera parameters
extern float cameraAngleX, cameraAngleY, cameraDistance;
extern float cameraPosX, cameraPosY;
extern bool perspective;
extern bool lightingEnabled;
extern bool shadowEnabled;

// Light parameters
extern float lightPosX, lightPosY, lightPosZ;

// Cube transformation parameters
extern float cubePosX, cubePosY, cubePosZ;
extern float cubeRotX, cubeRotY, cubeRotZ;
extern float cubeScale;

void initGL();
void Grid();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);

#endif

