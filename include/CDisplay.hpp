#ifndef C_DISPLAY_HPP
#define C_DISPLAY_HPP

#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#define KK .000001
#define REST (700000000 * KK)
#define REST_Z (REST)
#define REST_Y (-REST)
#define OFFSET (200000 * KK)
/**
 * Class to handle all the display functions.
 * For now this display class is implemented
 * using OpenGL framework. But it should have
 * been a derived class from the base display class.
 *
 */
class CDisplay {
   public:
    static void display(void);
    static void displayText(float x, float y, int r, int g, int b,
                            const char *string);
    static void reshape(int w, int h);

   private:
    static GLdouble eyeX, eyeY, eyeZ;
    static GLdouble centerX, centerY, centerZ;
    static GLdouble upX, upY, upZ;
    static double g;
    static GLdouble poX;
    static GLdouble poY;
    static GLdouble poZ;

    friend class CControl;
};

#endif