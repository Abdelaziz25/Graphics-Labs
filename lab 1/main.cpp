// Interaction:
// Press +/- to add/erase random point ---> good practice to add interaction as a comment at the top of source code

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/vec3.hpp>
#include <random>
#include <iostream>

//points: datastructure to store current points
std::vector<glm::vec3> points;
// window dimension
float windowWidth = 100.0;
float windowHeight = 100.0;

bool Draw = false;
// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(1.0); // Default line width.
	/*
	----------set point size below---------
	*/
		//code here
		glPointSize(5.0);
	//-------------------------------------
	/*
	----------write points drawing logic below------------
	*/
	glBegin(GL_POINTS);
		//code here
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < points.size(); i++) {
        glVertex3f(points[i].x, points[i].y, points[i].z);
    }
	glEnd();
	//----------------------------------------------------
	/*
	----------write lines drawing logic below------------
	*/
	  if (Draw) {
        glBegin(GL_LINES);
        //code here
        for (int i = 0; i < points.size() - 1; i += 2) {
        if (i > 0) {
            glColor3f(0.5f + 0.5f * (i % 3 == 0),
                      0.5f + 0.5f * (i % 3 == 1),
                      0.5f + 0.5f * (i % 3 == 2));
        }
        glVertex3f(points[i].x, points[i].y, points[i].z);
        glVertex3f(points[i+1].x, points[i+1].y, points[i+1].z);
    }
        glEnd();
    }

	//----------------------------------------------------
	glFlush();
}
// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	/*
	------------- Add +/- cases handling below (handle corner cases)----------------
	*/
		//code here
	//-----------------------------------------------------------------------
	 case '+':
         {
        float X = (float)rand() / RAND_MAX * windowWidth;
        float Y = (float)rand() / RAND_MAX * windowHeight;
        glm::vec3 point(X, Y, 0.0f);
        points.push_back(point);
         if(points.size()>1)
        {
            Draw = true;
        }
        glutPostRedisplay();
        break;
        }
     case '-':
		if (points.size() != 0) {
			points.pop_back();
			if (points.size() > 1) {
				Draw = true;
			}
			else
            {
                Draw = false;
            }
			glutPostRedisplay();
        }
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press +/- to add/erase random point" << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	printInteraction(); // good practice to print how to interact
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("RandomLines.cpp");
	glutDisplayFunc(drawScene);//drawing function
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);//handle keyboard events

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
