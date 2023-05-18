///////////////////////////////////////////////////////////////////////////////////////
// hemisphere.cpp
//
// This program approximates a hemisphere with an array of latitudinal triangle strips.
//
// Interaction:
// Press P/p to increase/decrease the number of longitudinal slices.
// Press Q/q to increase/decrease the number of latitudinal slices.
// Press x, X, y, Y, z, Z to turn the hemisphere.
//
// Sumanta Guha.
///////////////////////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static float R = 5.0; // Radius of hemisphere.
static int p = 6; // Number of longitudinal slices.
static int q = 4; // Number of latitudinal slices.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate hemisphere.
static float offset = -10;
static float spinSpeed = 5;
static float prev_time = 0;
bool filled = false;
bool isSphere = false;
const int num_turns = 5;
int num_vertices = 200;
float radius = 2.0f;
float pitch = 1.0f;

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Drawing routine.
void drawScene(void)
{

	int  i, j;

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	// Command to push the hemisphere, which is drawn centered at the origin,
	// into the viewing frustum.
	glTranslatef(0.0, 0.0, offset);

	// Commands to turn the hemisphere.
	glRotatef(Zangle, 0.0, 0.0, 1.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Xangle, 1.0, 0.0, 0.0);
    if(isSphere)
    {
         if(!filled)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
	// Hemisphere properties.

	glColor3f(0.0, 0.0, 0.0);

	// Array of latitudinal triangle strips, each parallel to the equator, stacked one
	// above the other from the equator to the north pole.
	for (j = 0; j < q; j++)
	{
		// One latitudinal triangle strip.
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= p; i++)
		{
			glVertex3f(R * cos((float)(j + 1) / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
				R * sin((float)(j + 1) / q * M_PI / 2.0),
				-R * cos((float)(j + 1) / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
			glVertex3f(R * cos((float)j / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
				R * sin((float)j / q * M_PI / 2.0),
				-R * cos((float)j / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
		}
		glEnd();
	}
	for (j = 0; j < q; j++)
	{
		// One latitudinal triangle strip.
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= p; i++)
		{
			glVertex3f(R * cos((float)(j + 1) / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
				-R * sin((float)(j + 1) / q * M_PI / 2.0),
				R * cos((float)(j + 1) / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
			glVertex3f(R * cos((float)j / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
				-R * sin((float)j / q * M_PI / 2.0),
				R * cos((float)j / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
		}
		glEnd();
	}
	glFlush();

    }
    else
    {
        for (int i = 0; i < num_turns; i++) {
        // Draw a segment of the helix
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j <= num_vertices; j++) {
            // Calculate the position of the current vertex
            float t = (float)j /num_vertices;
            float theta = t * 2.0f * M_PI * num_turns;
            float x = radius * cos(theta);
            float y = radius * sin(theta);
            float z = t * pitch + i;

            // Set the color of the current vertex to a random color
            glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);

            // Draw the current vertex
            glVertex3f(x, y, z);
        }
        glEnd();
    }
         glutSwapBuffers();
    }

}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void spinDisplay() {
	Yangle += spinSpeed * (glutGet(GLUT_ELAPSED_TIME) - prev_time) / 1000;
	prev_time = glutGet(GLUT_ELAPSED_TIME); // to indicate refresh rate
	if (Yangle > 360.0) Yangle -= 360.0;
	glutPostRedisplay();
}
void spinDisplayReverse() {

	Yangle -= spinSpeed * (glutGet(GLUT_ELAPSED_TIME) - prev_time) / 1000;
	prev_time = glutGet(GLUT_ELAPSED_TIME); // to indicate refresh rate
	std::cout << Yangle << std::endl;
	if (Yangle > 360.0) Yangle -= 360.0;
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplayReverse);

		break;

	default:
		break;
	}
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{

       switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'x':
		Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		Xangle -= 5.0;
		if (Xangle < 0.0) Xangle += 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		Yangle -= 5.0;
		if (Yangle < 0.0) Yangle += 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		Zangle -= 5.0;
		if (Zangle < 0.0) Zangle += 360.0;
		glutPostRedisplay();
		break;
	case 'O':
		offset += 1;
		glutPostRedisplay();
		break;
	case 'o':
		offset -= 1;
		glutPostRedisplay();
		break;
	case ' ':
		glutIdleFunc(NULL);
		break;
    if(isSphere)
    {
        case 'P':
		  p += 1;
		  glutPostRedisplay();
		  break;
	   case 'p':
		  if (p > 3) p -= 1;
		    glutPostRedisplay();
		  break;
	   case 'Q':
		  q += 1;
		  glutPostRedisplay();
		  break;
	   case 'q':
		 if (q > 3) q -= 1;
		 glutPostRedisplay();
		 break;
     case 'W':
		glClearColor(1.0, 1.0, 1.0, 0.0);
		filled = false;
		glutDisplayFunc(drawScene);
		glutPostRedisplay();
		break;
	 case 'w':
	    glClearColor(1.0, 1.0, 1.0, 0.0);
		filled = true;
		glutDisplayFunc(drawScene);
		glutPostRedisplay();
		break;
    }
    else
    {
        case 'R':
            radius += 0.1f;
            glutPostRedisplay();
            break;
        case 'r':
            radius -= 0.1f;
            glutPostRedisplay();
            break;
        case 'H':
            pitch += 0.1f;
            glutPostRedisplay();
            break;
        case 'h':
            pitch -= 0.1f;
            glutPostRedisplay();
            break;
        case 'N':
            num_vertices += 10;
            glutPostRedisplay();
            break;
        case 'n':
            num_vertices -= 10;
            glutPostRedisplay();
            break;
    }
	default:
		break;
	}


}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    if(isSphere)
    {
        std::cout << "Interaction:" << std::endl;
	    std::cout << "Press P/p to increase/decrease the number of longitudinal slices." << std::endl
		<< "Press Q/q to increase/decrease the number of latitudinal slices." << std::endl
		<< "Press W/w to draw  sphere in wireframe/filled sphere." << std::endl
		<< "Press x, X, y, Y, z, Z to turn the sphere." << std::endl;
    }
    else
    {
          std::cout << "Interaction:" << std::endl;
	    std::cout << "Press R/r to increase/decrease radius of the helix." << std::endl
		<< "Press H/h to increase/decrease pitch of helix." << std::endl
		<< "Press N/n to  increase/decrease number of vertices used to draw the helix" << std::endl
		<< "Press x, X, y, Y, z, Z to turn the helix." << std::endl;
    }
}

// Main routine.
int main(int argc, char** argv)
{

	glutInit(&argc, argv);
     std::cout << "Which shape do you want\n1) Helix\n2) Sphere\n>> ";
     std::string choice;
     std::getline(std::cin, choice);
     if (choice == "Helix")
    {
        isSphere= false;
    }
    else if (choice == "Sphere")
    {
        isSphere= true;
    }
    printInteraction();
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("helix or sphere.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouse);
	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
