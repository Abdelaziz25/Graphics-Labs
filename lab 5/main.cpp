///////////////////////////////////////////////////////////
// helixList.cpp
//
// This program draws several helixes using a display list.
//
// Sumanta Guha.
///////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
// Globals.
static unsigned int aStool; // List index.
static float xAngle= 0.0, yAngle = 0.0, zAngle = 0.0; // Angles for rotation.
static bool drawMode= true;
static unsigned int aStool2;
// Initialization routine.
void setup(void)
{
    float angle; // Angle parameter.
	aStool = glGenLists(1); // Return a list index.
    aStool2 = glGenLists(1);

	// Begin create a display list.
	// Draw the top of the stool.
    glNewList(aStool2, GL_COMPILE);
    float radius = 5.0, height = 1.0;
    int slices = 10, stacks = 3;
    glPushMatrix();

    if (drawMode) glutSolidCylinder(radius, height, slices, stacks);
    else
    {
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glutSolidCylinder(radius, height, slices, stacks);
    }
    glPopMatrix();
    glEndList();


    // Draw the three legs of the stool.
	glNewList(aStool, GL_COMPILE);
	radius = 0.5; height = 9.0;
    glPushMatrix();
    if (drawMode) glutWireCylinder(radius, height, slices, stacks);
    else
    {
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glutSolidCylinder(radius, height, slices, stacks);
    }
    glPopMatrix();
	glEndList();
	// End create a display list.
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Set up viewing transformation.
	glTranslatef(0.0, 3.0, -40.0);
	glRotatef(103.0, 90.0, 1.0, 0.0);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// Draw the stool using the display list.
    glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.252, 0.0, 0.0);
	glCallList(aStool2); // Execute display list.
	glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(-1.2, -1.5, 1.0);
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	glCallList(aStool); // Execute display list.
	glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(2.0, -1.5, 1.0);
    glRotatef(30.0, 0.0, 1.0, 0.0);
	glCallList(aStool); // Execute display list.
	glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.3, 3.0, 1.0);
	glRotatef(-30.0, 1.0, 0.0, 0.0);
	glCallList(aStool); // Execute display list.
	glPopMatrix();


	glFlush();
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5, 0.5, -0.5, 0.5, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
         xAngle -= 5.0;
        if (xAngle < -360.0) xAngle += 360.0;
        glutPostRedisplay();
        break;
    case 'X':
        xAngle += 5.0;
        if (xAngle > 360.0) xAngle -= 360.0;
        glutPostRedisplay();
        break;
    case 'y':
         yAngle -= 5.0;
        if (yAngle < -360.0) yAngle += 360.0;
        glutPostRedisplay();
        break;
    case 'Y':
        yAngle += 5.0;
        if (yAngle > 360.0) yAngle -= 360.0;
        glutPostRedisplay();
        break;
    case 'z':
        zAngle -= 5.0;
        if (zAngle < -360.0) zAngle += 360.0;
        glutPostRedisplay();
        break;
    case 'Z':
        zAngle += 5.0;
        if (zAngle > 360.0) zAngle -= 360.0;
        glutPostRedisplay();
        break;
    case ' ':
        drawMode = !drawMode;
        setup();
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3-Legged Stool");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glewExperimental = GL_TRUE;
    glewInit();
    setup();
    glutMainLoop();
}
