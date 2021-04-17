#include <cmath>

#include "CControl.hpp"
#include "CDisplay.hpp"
#include "CPlanet.hpp"
#include "CSolar.hpp"

using namespace std;
CSolar Solar;
CPlanet* P;

void drawScene2() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glBegin(GL_QUADS);

    // rectangle

    glVertex3f(0.0f, 0.0f, -5.0f);

    glVertex3f(0.0f, 1.0f, -5.0f);

    glVertex3f(1.0f, 1.0f, -5.0f);

    glVertex3f(1.0f, 0.0f, -5.0f);

    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    CControl Control;
    Control.init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(2000, 100);
    glutCreateWindow("Gravitational Laboratory");
    // register function to display on the window
    glutDisplayFunc(CDisplay::display);
    // register function to reshape the size of the window
    glutReshapeFunc(CDisplay::reshape);
    // register function to receive the command from the keyboard
    glutKeyboardFunc(CControl::keyboard);
    // register function to receive the motion action from the mouse
    glutMotionFunc(CControl::motion);
    // register function to receive the button action from the mouse
    glutMouseFunc(CControl::mouse);
    // register function to update the state of the system
    glutIdleFunc(CControl::UpdateState);

    // the second window for monitoring the energy and momentum
	/*
    glutCreateWindow("Monitor");
    glutPositionWindow(2400, 100);
	glutDisplayFunc(drawScene2);
	*/
    // the main loop of the entire graphics program
    glutMainLoop();
    return 0;
}