#include<windows.h>
#include<GL/glut.h>
static GLfloat spin=3.0;
void display_ROTATE()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin,0.0,0.0,1.0);
	glColor3f(1.0,0.5,0.0);
	glRectf(-0.5,-0.5,0.5,0.5);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	
}
void display_idle()
{
	spin=spin+0.01;
	if(spin>=360)
		spin=spin-360;
	glutPostRedisplay();
}
void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0,-50.0,-50.0,50.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void mouse(int Button,int state,int x,int y)
{
	switch(Button)
	{
	case GLUT_LEFT_BUTTON:
			if (state==GLUT_DOWN)
			glutIdleFunc(&display_idle);
			break;
	case GLUT_RIGHT_BUTTON:
			if(state==GLUT_DOWN)
			glutIdleFunc(NULL);
			break;
	default:
			break;
	}
}
void display_slice()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSolidSphere(0.4,spin,2);
	glFlush();
	glutSwapBuffers();
}
void init()
{
	glShadeModel(GL_FLOAT);
	glClearColor(0.3,0.3,0.3,0.0);
	
}

void main()
{
	glutCreateWindow("");
	init();
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	//glutDisplayFunc(&display_ROTATE);
	glutDisplayFunc(&display_slice);
	glutReshapeFunc(&reshape);
	glutMouseFunc(&mouse);
	glutMainLoop();
}
