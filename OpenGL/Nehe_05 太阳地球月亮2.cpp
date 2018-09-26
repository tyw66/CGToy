#include<GL/glut.h>

void myDisplay()
{
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_POINTS);
		glVertex2f(0.0,0.0);
	glEnd;
	//glTranslatef(15,0.0f,0.0f);
	glFlush;
}
int main2()
{
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("ÐÇÇò");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}