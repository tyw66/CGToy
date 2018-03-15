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
	glMatrixMode(GL_PROJECTION);		//����һ������Ϊ��ǰ�������ΪͶӰ�任����
	glLoadIdentity();					//��λ��
	gluPerspective(80,1,1,400);	
	
	
	glMatrixMode(GL_MODELVIEW);		//����һ������Ϊ��ǰ�������Ϊ����任����
	glLoadIdentity();
	gluLookAt(0,100,10,0,0,0,0,1,0);

	

	glColor3f(1.0f,0.0f,0.0f);		//̫��
	glutSolidSphere(10,20,20);	

	glColor3f(0.0f,0.0f,1.0f);		//����
	glRotatef(day,0.0f,1.0f,0.0f);
	glTranslatef(20,0.0f,0.0f);		
	glutSolidSphere(4,20,20);

	glColor3f(1.0f,1.0f,0.0f);
	glRotatef(day/30.0*360.0,0.0f,1.0f,0.0f);
	glTranslatef(7,0.0f,0.0f);
	glutSolidSphere(1,20,20);		//����

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
	glutCreateWindow("����");
	glutDisplayFunc(&Display);
	glutIdleFunc(&Idle);
	glutMainLoop();
	return 0;
}
