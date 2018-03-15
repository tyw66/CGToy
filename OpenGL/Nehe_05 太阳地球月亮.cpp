#include<GL/glut.h>

static int day=200;
void Display()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f,0.5f,0.5f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);		//建立一矩阵并设为当前活动，类型为坐标变换矩阵
	glLoadIdentity();
	gluLookAt(-200000000,0,0,0,0,0,0,0,1);
	glMatrixMode(GL_PROJECTION);		//建立一矩阵并设为当前活动，类型为投影矩阵
	glLoadIdentity();					//单位化
	gluPerspective(75,1,1,400000000);		
	

	glColor3f(1.0f,0.0f,0.0f);
	glutSolidSphere(69600000,20,20);
	glColor3f(0.0f,0.0f,1.0f);
	glRotatef(day/360.0*360.0,0.0f,0.0f,-1.0f);
	glTranslatef(150000000,0.0f,0.0f);
	glutSolidSphere(15945000,20,20);
	glColor3f(1.0f,1.0f,0.0f);
	glRotatef(day/30.0*360.0-day/360.0*360.0,0.0f,0.0f,-1.0f);
	glTranslatef(38000000,0.0f,0.0f);
	glutSolidSphere(4345000,20,20);

	glFlush();
}

int main()
{
	
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("星球");
	glutDisplayFunc(&Display);
	glutMainLoop();
	return 0;
}
