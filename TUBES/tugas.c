#include "tugas.h"
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Light status
bool lightOn = true;

// Window dimensions
int windowWidth = 800;
int windowHeight = 600;

// Camera parameters
float cameraAngleX = 0.0f; // Start looking down at the object
float cameraAngleY = 10.0f;
float cameraDistance = 10.0f;
float cameraPosX = 0.0f, cameraPosY = 1.0f; // Start above the cube
bool perspective = true;
bool lightingEnabled = true;
bool shadowEnabled = true;


// Light parameters
const float lightConstPosX = 2.0f;
const float lightConstPosY = 2.0f;
const float lightConstPosZ = 2.0f;
float lightPosX = lightConstPosX;
float lightPosY = lightConstPosY;
float lightPosZ = lightConstPosZ;

// Cube transformation parameters
float cubePosX = 0.0f, cubePosY = 0.5f, cubePosZ = 0.0f;
float cubeRotX = 0.0f, cubeRotY = 0.0f, cubeRotZ = 0.0f;
float cubeScale = 1.0f;
bool cubeEnabled = true;

// Light movement parameters
float lightAngle = 0.0f;

void initGL() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glEnable(GL_LIGHTING);   // Enable lighting
    glEnable(GL_LIGHT0);     // Enable light #0
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set background color
    glShadeModel(GL_SMOOTH); // Enable smooth shading
}


void updateLightPosition() {
    
    if (lightAngle > 360.0f) lightAngle -= 360.0f;
    lightPosX = 5.0f * cos(lightAngle);
    lightPosZ = 5.0f * sin(lightAngle);
}

void Grid() {
    const float Z_MIN = -50.0f, Z_MAX = 50.0f;
    const float X_MIN = -50.0f, X_MAX = 50.0f;
    const float gap = 2.0f;

    GLfloat matAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat matDiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat matSpecular[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat matShininess[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    glColor3f(0.5f, 0.5f, 0.5f);
    for (float i = X_MIN; i < X_MAX; i += gap) {
        for (float j = Z_MIN; j < Z_MAX; j += gap) {
            glBegin(GL_QUADS);
            glNormal3f(0.0f, 1.0f, 0.0f); // Set normal for lighting
            glVertex3f(i, 0, j);
            glVertex3f(i + gap, 0, j);
            glVertex3f(i + gap, 0, j + gap);
            glVertex3f(i, 0, j + gap);
            glEnd();
        }
    }
}

void drawCube() {
    if (cubeEnabled) {
        glPushMatrix(); // Save the current state of transformations
        // Apply cube transformations
        glTranslatef(cubePosX, cubePosY, cubePosZ);
        glRotatef(cubeRotX, 1.0f, 0.0f, 0.0f);
        glRotatef(cubeRotY, 0.0f, 1.0f, 0.0f);
        glRotatef(cubeRotZ, 0.0f, 0.0f, 1.0f);
        glScalef(cubeScale, cubeScale, cubeScale);

        // Draw the cube
        glColor3f(0.5f, 0.5f, 0.5f);
        glutSolidCube(1.0);
        glPopMatrix(); // Restore the previous state of transformations
    }
}

void drawLightSource() {
    glPushMatrix(); // Save the current state of transformations
    glTranslatef(lightPosX, lightPosY, lightPosZ);
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix(); // Restore the previous state of transformations
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void setupLight() {
    if (lightOn && lightingEnabled) {
        glEnable(GL_LIGHT0);
        GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat lightPos[] = { lightPosX, lightPosY, lightPosZ, 1.0f };

        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    } else {
        glDisable(GL_LIGHT0);
    }
}


void drawShadow() {
    if (shadowEnabled) {
        float shadowMat[16] = {
            lightPosY, 0, 0, 0,
            -lightPosX, 0, -lightPosZ, -1,
            0, 0, lightPosY, 0,
            0, 0, 0, lightPosY
        };

        glPushMatrix();
        glMultMatrixf(shadowMat);
        glDisable(GL_LIGHTING);
        glColor3f(0.1f, 0.1f, 0.1f);
        drawCube();
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
}



void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (perspective) {
        gluLookAt(cameraPosX, cameraPosY, cameraDistance, cameraPosX, cameraPosY, 0, 0, 1, 0);
    } else {
        glOrtho(-cameraDistance, cameraDistance, -cameraDistance, cameraDistance, -cameraDistance, cameraDistance);
    }

    glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);

    updateLightPosition(); // Update the light position
    setupLight(); // Set up the light source

    // Draw the grid
    Grid();

    // Draw the shadows
    drawShadow();

    // Draw the cube
    drawCube();

    // Draw the light source
    drawLightSource();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'p':
        perspective = !perspective;
        break;
    case 'L':
        lightingEnabled = !lightingEnabled;
        break;
    case 'S':
        shadowEnabled = !shadowEnabled;
        break;
    case 'w': // Move cube up
        cubePosY += 0.1f;
        if (cubePosY - 0.5f * cubeScale < 0.0f) cubePosY = 0.5f * cubeScale; // Collision with floor
        break;
    case 'a': // Move cube left
        cubePosX -= 0.1f;
        break;
    case 's': // Move cube down
        cubePosY -= 0.1f;
        if (cubePosY - 0.5f * cubeScale < 0.0f) cubePosY = 0.5f * cubeScale; // Collision with floor
        break;
    case 'd': // Move cube right
        cubePosX += 0.1f;
        break;
    case 'q': // Move cube forward
        cubePosZ += 0.1f;
        break;
    case 'e': // Move cube backward
        cubePosZ -= 0.1f;
        break;
    case '=': // Scale up
        cubeScale += 0.1f;
        break;
    case '-': // Scale down
        cubeScale -= 0.1f;
        if (cubeScale < 0.1f) cubeScale = 0.1f; // Prevent scaling to zero or negative
        break;
    case 'i': // Rotate cube up
        cubeRotX += 5.0f;
        break;
    case 'k': // Rotate cube down
        cubeRotX -= 5.0f;
        break;
    case 'j': // Rotate cube left
        cubeRotY -= 5.0f;
        break;
    case 'l': // Rotate cube right
        cubeRotY += 5.0f;
        break;
    case 'u': // Rotate cube counter-clockwise
        cubeRotZ -= 5.0f;
        break;
    case 'o': // Rotate cube clockwise
        cubeRotZ += 5.0f;
        break;
    case 'P':
        lightOn = !lightOn; // Toggle light on/off
        break;

    // Camera panning
    case 'r':
        cameraPosY += 0.1f;
        break;
    case 'f':
        cameraPosY -= 0.1f;
        if (cameraPosY < 0.0f) cameraPosY = 0.0f; // Prevent moving below platform
        break;
    case 't':
        cameraPosX += 0.1f;
        break;
    case 'g':
        cameraPosX -= 0.1f;
        break;

    // Camera zooming
    case '+':
        cameraDistance -= 0.1f;
        if (cameraDistance < 1.0f) cameraDistance = 1.0f; // Prevent zooming too close
        break;
    case '_':
        cameraDistance += 0.1f;
        break;
        
    case '[':
    	 lightAngle += 0.01f;
    	 break;
    	 
	case ']':
		lightAngle-= 0.01f;
		break;
    	
    }

    glutPostRedisplay();
}


void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_DOWN:
        if (cameraAngleX > 0.0f) { // Prevent exceeding -90 degrees
            cameraAngleX -= 5.0f;
        }
        break;
    case GLUT_KEY_UP :
        if (cameraAngleX < 160.0f) { // Prevent exceeding 90 degrees
            cameraAngleX += 5.0f;
        }
        break;
    case GLUT_KEY_LEFT:
        cameraAngleY -= 5.0f;
        break;
    case GLUT_KEY_RIGHT:
        cameraAngleY += 5.0f;
        break;
    }
    glutPostRedisplay();
}



void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Toggle cube drawing
        cubeEnabled = !cubeEnabled;
        glutPostRedisplay();
    }
}

void motion(int x, int y) {
    // Implement camera panning and zooming
}




