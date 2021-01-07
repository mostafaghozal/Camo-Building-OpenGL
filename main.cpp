/// **            Mostafa Ashraf                                              18107667                                              **///
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cassert>
#include <windows.h>
#include <iostream>
#include <string>
#include <random>
#include "rgbpixmap.cpp"
using namespace std;
///                               ***                   Screen Settings & positioning                  ***
bool fullScreenMode = true;
double windowPosX = 10;
double windowPosY = 30;
double windowWidth = glutGet(GLenum GLUT_SCREEN_WIDTH)-30;
double windowHeight = glutGet(GLenum GLUT_SCREEN_HEIGHT)-20;
///                               ***                   ESC & F11                 ***
void keyBoard(unsigned char key, int x, int y)
{
    switch(key)
    {

    case 27:
        exit(0);
    }
}

void specialKeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_F1:    /// F1: Toggle between full-screen and windowed mode
        fullScreenMode = !fullScreenMode;         /// Toggle state
        if (fullScreenMode)                       /// Full-screen mode
        {
            windowPosX   = glutGet(GLUT_WINDOW_X); /// Save parameters for restoring later
            windowPosY   = glutGet(GLUT_WINDOW_Y);
            windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
            windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
            glutFullScreen();                      /// Switch into full screen
        }
        else                                             /// Windowed mode
        {
            glutReshapeWindow(windowWidth, windowHeight); /// Switch into windowed mode
            glutPositionWindow(windowPosX, windowPosX);   /// Position top-left corner
        }
        break;
    }
}

///                               ***                  Defintions & Declrations to be used later in code                 ***

#define PI 3.1415926535897932384626433832795
#define MaximumTheta 1.0
#define MinimumTheta 0.0009
#define MaximumRadious 10.5
#define MinimumRadious .9

int width =  glutGet(GLenum GLUT_SCREEN_WIDTH);
int height =  glutGet(GLenum GLUT_SCREEN_HEIGHT);


GLfloat IncrementTheta = 0.05;
GLint WindowSizX=width,WindowSizY=height;

GLfloat EyePosition_X=2.0,EyePosition_Y=1.3,EyePosition_Z= 2.0;
GLfloat Radious=3.3,ProRadious=3.0,InitialTheta1=0.716,InitialTheta2=0.403;

GLfloat Center_X=0.0,Center_Y=0.0,Center_Z=0.0;
GLfloat Up_X=0.0,Up_Y=1.0,Up_Z=0.0;

enum { ClockWise,AntiClockWise };
enum {Theta1,Theta2};

float Near=.05, Far=10.0,fova = 50.0;

GLint direction = AntiClockWise;
GLint PressMovenent=Theta1;

RGBpixmap pix[15];


void CalculationX_Y_Z();
void CalculationTH1();
void CalculationTH2();
void Movenent();
GLUquadricObj *cone, *base, *qsphere, *cylinder;



///                               ***                  Preparing our shapes in functions                ***

void buildingBlock()
{

    double topWidth = 0.6;
    double topThick = 0.02;
    double legThick = 0.02;
    double legLen = 0.3;

    glPushMatrix();
    glTranslated(0, legLen, 0);
    glScaled(topWidth, topThick, topWidth);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(topWidth, topThick, topWidth);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glPopMatrix();

    /// Solid Cube
    glPushMatrix();
    glScaled(1,0.5,1);
    glTranslated(0,0.3,0);
    glutSolidCube(0.55);
    glPopMatrix();


    double dist = 0.95 * topWidth/2.0 - legThick/2.0;

}
void floor()
{

    double topWidth = 0.6;
    double topThick = 0.02;
    double legThick = 0.02;
    double legLen = 0.3;

    glPushMatrix();
    glTranslated(0, legLen, 0);
    glScaled(topWidth, topThick, topWidth);
    glutSolidCube(1.0);
    glPopMatrix();
}

void building()
{
    glPushMatrix();
    glTranslated(0.4, 0, 0.4);
    glBindTexture(GL_TEXTURE_2D,2);
    glEnable(GL_TEXTURE_2D);

    buildingBlock();
    glTranslated(0,0.30,0);
    buildingBlock();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}

void roadFunc()
{
    double topWidth = 0.6;
    double topThick = 0.02;
    double legThick = 0.02;
    double legLen = 0.3;

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTranslated(0, legLen, 0);
    glScaled(topWidth, topThick, topWidth);
    glutSolidCube(1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void door()
{

    GLfloat lightIntensity[] = {2.7f, 2.7f, 2.7f, 1.0f};
    GLfloat lightPosition[] = {2.0f, 6.0f, 3.0f, 0.0f};


    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,8);
    glEnable(GL_TEXTURE_2D);
    roadFunc();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}
 /// same as door b but diff positions
void door1()
{
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glScalef(0.5, 1, 1);
    glTranslated(0,.5,-0.5);
    door();
    glPopMatrix();
}

void doorFinal()
{

    glPushMatrix();
    glTranslated(-0.22,-0.18,-0.9);
    glScalef(1,0.8,1);
    door1();
    glPopMatrix();
}


void windowFunction()
{
 glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslated(1, 0.2, 0);
    doorFinal();

    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    glScalef(1, 1, 0.8);
    glPushMatrix();
    glTranslated(0, 0, 0.65);
    doorFinal();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}
/// same as window but diff positions

void finalWindow1()
{
    glPushMatrix();
    glTranslated(-0.28,0.1,-0.07);
    windowFunction();
    glPopMatrix();
}

void twofinalWindow()
{
    glPushMatrix();
    finalWindow1();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.67, 0, 0);
    finalWindow1();
    glPopMatrix();
}

void sideFinalWindow()
{
    glPushMatrix();
    glTranslated(0.48, 0.59, -0.3);
    glRotated(90, 0, 1, 0);
    finalWindow1();
    glPopMatrix();
}
///                             ***                   Text Function                 ***
 void drawText(const char *text, int length, int x,int y)
  {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0,600, 0, 400, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
  glPushMatrix();
    glColor3f(1, 0, 0);
    glRasterPos2i(x, y);
    for (int i=0;i<length;i++)
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
  }

void display(void)
{
    ///                            ***                  LIGHT                 ***
    GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat mat_defused[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {50.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_defused);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


    GLfloat lightIntensity[] = {1.7f, 1.7f, 1.7f, 1.0f};
    GLfloat lightPosition[] = {2.0f, 6.0f, 3.0f, 0.0f};


    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    glViewport(0, 0, WindowSizX,WindowSizY );


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
///                               ***                   Screen Settings & positioning                  ***
    float aspectR = (float)WindowSizX / WindowSizY;

    gluPerspective(fova,aspectR, Near, Far);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(EyePosition_X,EyePosition_Y,EyePosition_Z,Center_X,Center_Y,Center_Z,Up_X,Up_Y,Up_Z);

///                               ***                   Drawing all              ***
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    ///  Building Block

    glPushMatrix();
        glTranslated(-1,0,-0.8);
        glScalef(2, 2,1);
        building();
    glPopMatrix();

    //// floor
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,4);
    glEnable(GL_TEXTURE_2D);
    glScalef(4,1,4);
    glTranslated(0,-0.33,0);
    floor();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /// door final

    glPushMatrix();
    doorFinal();
    glPopMatrix();

    /// window down

    glPushMatrix();
    twofinalWindow();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0.6, 0);
    twofinalWindow();
    glPopMatrix();


    /// side final window

    glPushMatrix();
    sideFinalWindow();
    glPopMatrix();


    glPushMatrix();
    glTranslated(0, -0.6, 0);
    sideFinalWindow();
    glPopMatrix();
///                               ***                   Text               ***
std::string text;
text="Controls: ";
drawText(text.data(),text.size(),10,360);
text="Zoom in : + , Zoom out : -";
drawText(text.data(),text.size(),10,350);
text="Controls: UP : 2 , Down : 8";
drawText(text.data(),text.size(),10,340);
text="Controls: RIGHT : 4 , LEFT : 6";
drawText(text.data(),text.size(),10,330);
text="Mostafa Ashraf 18107667";
drawText(text.data(),text.size(),430,30);
    glFlush();

    glutSwapBuffers();
}

void RepeatDisplay()
{
    glutPostRedisplay();
}
///                               ***                  CAMERA functions               ***
void Movenent()
{

    CalculationX_Y_Z();

    if(PressMovenent == Theta1)
        CalculationTH1();
    else
        CalculationTH2();

}
void CalculationX_Y_Z()
{
    ProRadious = Radious * cos(InitialTheta2);
    EyePosition_Y = Radious * sin(InitialTheta2);

    EyePosition_X = ProRadious * cos(InitialTheta1);
    EyePosition_Z = ProRadious * sin(InitialTheta1);

    printf("EyePosition_X: %f\n",EyePosition_X);
    printf("EyePosition_Y: %f\n",EyePosition_Y);
    printf("EyePosition_Z: %f\n\n",EyePosition_Z);
}

void CalculationTH1()
{
    if (InitialTheta1 > PI*2)
        InitialTheta1 = 0.0;
    if(direction == AntiClockWise)
    {
        InitialTheta1 += IncrementTheta;
        printf("InitialTheta1: %f\n",InitialTheta1);
    }
    else
        InitialTheta1 -= IncrementTheta;
    printf("InitialTheta1: %f\n",InitialTheta1);
}

void CalculationTH2()
{
    if (InitialTheta2 > PI*2)
        InitialTheta2 = 0.0;

    if(direction == AntiClockWise)
    {
        InitialTheta2 += IncrementTheta;
        printf("InitialTheta2: %f\n",InitialTheta2);
    }

    else
        InitialTheta2 -= IncrementTheta;
    printf("InitialTheta2: %f\n",InitialTheta2);

}
///                               ***                   Pass parameter "key"                  ***
void CalculationRadious(unsigned int key)
{

    if(key == '-')
    {
        if(Radious > MaximumRadious)
            Radious = MaximumRadious;
        else
            Radious += 0.2;
        printf("Radious: %f\n",Radious);
    }
    else if(key == '+')
    {
        if(Radious <= MinimumRadious)
            Radious = MinimumRadious;
        else
            Radious -= 0.2;
        printf("Radious: %f\n",Radious);
    }

    CalculationX_Y_Z();
}

///                               ***                   Key Presses                 ***
void KeybordFunction( unsigned char key, int x, int y )
{

    if(key=='-')

        CalculationRadious(key);

    else if(key=='+')
        CalculationRadious(key);

    else if(key == '4') ///
    {
        direction = ClockWise;
        PressMovenent = Theta1;
        Movenent();
    }

    else if(key == '6')
    {

        direction = AntiClockWise;
        PressMovenent = Theta1;
        Movenent();
    }
    else if(key == '8')
    {

        direction = ClockWise;
        PressMovenent = Theta2;
        Movenent();
    }
    else if(key == '2')
    {

        direction = AntiClockWise;
        PressMovenent = Theta2;
        Movenent();
    }
    else if(key == 27)  exit(0);

}
///                               ***                  TEXTURING               ***
void Init()
{
    glEnable(GL_TEXTURE_2D);
    pix[0].makeCheckImage();
    pix[0].setTexture(1);	/// create texture int parameter as TextureName
    pix[1].readBMPFile("galvanized_dark.bmp");
    pix[1].setTexture(2);

    pix[3].readBMPFile("SAND3.bmp");
    pix[3].setTexture(4);
    pix[7].readBMPFile("ring_bottoms.bmp");
    pix[7].setTexture(8);

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(windowPosX, windowPosY);
    glutInitWindowSize(WindowSizX, WindowSizY);
    glutCreateWindow("Building");
    glutKeyboardFunc(KeybordFunction);
    glutIdleFunc(RepeatDisplay);
    glutDisplayFunc(display);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glutSpecialFunc(specialKeys);
    glutFullScreen();
    Init();
    glutMainLoop();
    return 0;
}
