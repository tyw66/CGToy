#include<GL/glut.h>
#include<GL/GL.h>
void DreaGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-1.5f,0.0f,-6.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,0.0f);
		glVertex3f(1.0f,-1.0f,0.0f);
	glEnd();
	glTranslatef(3.0f,0.0f,0.0f);
	
	glBegin(GL_QUADS);
		glVertex3f(-1.0f,1.0f,0.0f);
		glVertex3f(1.0f,1.0f,0.0f);
		glVertex3f(1.0f,-1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,0.0f);
	glEnd();
	
}
void main()
{
	glutCreateWindow("三角形与矩形");
	glutDisplayFunc(&DreaGLScene);
	glutMainLoop();

}