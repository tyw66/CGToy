#include<GL/glut.h>
#include<gl/GL.h>
int i;

void init()
{
	glShadeModel(GL_FLOAT);
	glClearColor(0.3,0.3,0.3,0.0);
	
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
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for(i=0.1;i<=1;i++)
	{
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0,1.0,0.0);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(0.0,i,i);
			glVertex3f(0.0,-i,-i);
			glEnd();
			glFlush();

	}
}


void main()
{
	glutCreateWindow("");
	init();
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutDisplayFunc(&draw);
	glutReshapeFunc(&reshape);
	glutMainLoop();
}
