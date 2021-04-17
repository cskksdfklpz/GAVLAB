#include "CDisplay.hpp"
#include "CPlanet.hpp"
#include "CControl.hpp"
#include "CSolar.hpp"

#include <cstring>

GLdouble CDisplay::eyeX = 2.8;
GLdouble CDisplay::eyeY = 1.4;
GLdouble CDisplay::eyeZ = 2.4;
GLdouble CDisplay::centerX = 0;
GLdouble CDisplay::centerY = 0;
GLdouble CDisplay::centerZ = 0;
GLdouble CDisplay::upX = 0;
GLdouble CDisplay::upY = 0;
GLdouble CDisplay::upZ = 1;
double CDisplay::g = 1.;
GLdouble CDisplay::poX = 0.0;
GLdouble CDisplay::poY = 0.0;
GLdouble CDisplay::poZ = 0.0;


void CDisplay::display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0.1, 1);
    glShadeModel(GL_SMOOTH);

    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0f, 1.0f, 1.0f, 40000000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    displayText(100,100,255,255,255,"Hello");
    glColor3f(1.0f, 1.0f, 1.0f);  //指定线的颜色,白色
    glLineWidth(0.1);
    // x-axis
    for (int y = -300; y <= 300; y += 5) {
        glBegin(GL_LINE_STRIP);
        {
            glVertex3f(-300.0f, y, 0.0f);
            glVertex3f(300.0f, y, 0.0f);
        }
        glEnd();
    }

    for (int x = -300; x <= 300; x += 5) {
        glBegin(GL_LINE_STRIP);
        {
            glVertex3f(x, -300.0f, 0.0f);
            glVertex3f(x, 300.0f, 0.0f);
        }
        glEnd();
    }

    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(.03, 100, 100);

    vector<CPlanet>::iterator itr;
    // draw the tragetory here
    for (itr = Solar.Stars.begin(); itr != Solar.Stars.end(); itr++) {
        GLfloat r = itr->Red(), g = itr->Green(), b = itr->Blue();
        glColor3f(r, g, b);  // color of the line
        glLineWidth(2);
        glBegin(GL_LINE_STRIP);
        {
            list<vector3d>::iterator p;
            for (p = itr->trail.begin(); p != itr->trail.end(); p++) {
                poX = p->X() / SCALE;
                poY = p->Y() / SCALE;
                poZ = p->Z() / SCALE;
                glVertex3d(-poX, poY, poZ);
            }
        }
        glEnd();
    }

    if (CControl::ShowRecord == true && CControl::play == true) {
        printf("\n\n\n>>Time/DAY:%lf\n", Solar.GetT() / DAY);
    }

    for (itr = Solar.Stars.begin(); itr != Solar.Stars.end(); itr++) {
        if (itr->Exist() == false) {
            if (CControl::ShowRecord == true && CControl::play == true) {
                printf("-----------------%s----------------\n",
                       itr->GetName().c_str());
                printf(">>Boomed\n");
            }
            continue;
        }

        GLfloat r = itr->Red(), g = itr->Green(), b = itr->Blue();
        double radius = 0.03 * itr->GetRadius();
        glColor3f(r, g, b);
        poX = itr->X() / SCALE;
        poY = itr->Y() / SCALE;
        poZ = itr->Z() / SCALE;
        glTranslated(-poX, poY, poZ);
        glutSolidSphere(radius, 100, 100);
        glTranslated(poX, -poY, -poZ);

        if (CControl::ShowRecord == true && CControl::play == true) {
            printf("-----------------%s----------------\n",
                   itr->GetName().c_str());
            printf(">> mass/KG:");
            printf("%e\n", itr->GetMass() * 1e18);
            printf(">>v/ms-1:");
            printf("(%lf,%lf,%lf)\n", itr->GetV().X(), itr->GetV().Y(),
                   itr->GetV().Z());
            printf(">>r/m:");
            printf("(%lf,%lf,%lf)\n", itr->X(), itr->Y(), itr->Z());
        }
    }

    

    glPopMatrix();

    glFlush();
}

void CDisplay::displayText(float x, float y, int r, int g, int b,
                            const char *string) {
        int j = strlen(string);

        glColor3f(r, g, b);
        glRasterPos2f(x, y);
        for (int i = 0; i < j; i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
        }
    }

void CDisplay::reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, -20.0f, -150.0f);
}