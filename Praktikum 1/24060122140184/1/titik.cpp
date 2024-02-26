#include <GL/glut.h>

void point(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(15.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(0.25, 0.30, 0.0);
    glVertex3f(0.25, 0.35, 0.0);
    glVertex3f(0.25, 0.40, 0.0);
    glVertex3f(0.25, 0.45, 0.0);
    glColor3f(0.0f, 3.0f, 0.0f);
    glVertex3f(0.25, 0.50, 0.0);
    glColor3f(1.0f, 2.0f, 0.0f);
    glVertex3f(0.25, 0.55, 0.0);
    glColor3f(1.0f, 1.0f, 3.0f);
    glVertex3f(0.25, 0.60, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Titik");
    glutDisplayFunc(point);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutMainLoop();
    return 0;
}


