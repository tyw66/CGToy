#include<GL/glut.h>
#include<time.h>
#include<stdio.h>

static float day=100;

double CalFrequency()
{
	static int count;
	static double save;
	static clock_t last,current;
	double timegap;

	++count;
	if(count<=50)
		return save;
	count=0;
	last=current;
	current=clock();
	timegap=(current-last)/(double)CLK_TCK;
	save=50.0/timegap;
	return save;
}

void Display()
{
	double FPS=CalFrequency();
	printf("FPS=%f\n,FPS");

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f,0.5f,0.5f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);		//建立一矩阵并设为当前活动，类型为投影变换矩阵
	glLoadIdentity();					//单位化
	gluPerspective(80,1,1,400);	
	
	
	glMatrixMode(GL_MODELVIEW);		//建立一矩阵并设为当前活动，类型为坐标变换矩阵
	glLoadIdentity();
	gluLookAt(0,100,10,0,0,0,0,1,0);

	

	glColor3f(1.0f,0.0f,0.0f);		//太阳
	glutSolidSphere(10,20,20);	

	glColor3f(0.0f,0.0f,1.0f);		//地球
	glRotatef(day,0.0f,1.0f,0.0f);
	glTranslatef(20,0.0f,0.0f);		
	glutSolidSphere(4,20,20);

	glColor3f(1.0f,1.0f,0.0f);
	glRotatef(day/30.0*360.0,0.0f,1.0f,0.0f);
	glTranslatef(7,0.0f,0.0f);
	glutSolidSphere(1,20,20);		//月亮

	glFlush();
	glutSwapBuffers();
}

void Idle(void)
{
	day+=0.01;
	if(day>=360)
		day=0;
	Display();
}

int main()
{
	
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(600,600);
	glutCreateWindow("星球");
	glutDisplayFunc(&Display);
	glutIdleFunc(&Idle);
	glutMainLoop();
	return 0;
}
