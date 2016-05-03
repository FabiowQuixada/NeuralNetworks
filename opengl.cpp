#include <GL/glut.h>

GLfloat windowWidth  = 400;
GLfloat windowHeight = 350;

void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

#include "point.h"

void display()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Cleans the screen with the color defined in the init() function;
	glClear(GL_COLOR_BUFFER_BIT);

	Point p;

	p.draw();

		glBegin(GL_LINE_LOOP);
		glVertex2f(1            , 0               );
		glVertex2f(2*windowWidth, 0               );
		glVertex2f(2*windowWidth, 2*windowHeight  );
		glVertex2f(0            , 2*windowHeight-1);
	glEnd();

	glutSwapBuffers();
}

void timer(int value)
{
	// Redraws the scene;
	glutPostRedisplay();
	glutTimerFunc(33,timer,1);
}

void resize(GLsizei w, GLsizei h)
{
	if(h == 0) h = 1;

	// Defines the lower left and the top right corners of the scene in pixels;
	glViewport(0,0,w,h);
	windowWidth = w;
	windowHeight = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Viewing volume: -x, x, -y, y;
	glOrtho(0, 2*w, 0, 2*h,-1,1);
}

void mouseHandling(int button, int state, int x, int y)
{
	glutPostRedisplay();
}

void keyboardHandling(unsigned char key, int x, int y)
{
	switch(key)
	{
	}

	glutPostRedisplay();
}
