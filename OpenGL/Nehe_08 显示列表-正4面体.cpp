#include<GL/glut.h>
#include<math.h>
#define WIDTH 800
#define HEIGHT 800
#define ColoredVertex(c,v)do{glColor3fv(c);glVertex3fv(v);}while(0)

GLfloat angle=0.0f;

void Display()
{
	static int list=0;
	if(list==0)
	{
	GLfloat
		PointA[]={0.5f,-sqrt(6.0f)/12,-sqrt(3.0f)/6},
		PointB[]={-0.5f,-sqrt(6.0f)/12,-sqrt(3.0f)/6},
		PointC[]={0.0f,-sqrt(6.0f)/12,sqrt(3.0f)/3},
		PointD[]={0.0f,sqrt(6.0f)/4,0};

	GLfloat
		ColorR[]={1,0,0},
		ColorG[]={0,1,0},
		ColorB[]={0,0,1},
		ColorY[]={1,1,0};
	
	list=glGenLists(1);
	glNewList(list,GL_COMPILE);
	//��ʼװ��OP����
	glBegin(GL_TRIANGLES);
	//ƽ��abc
	ColoredVertex(ColorR,PointA);
	ColoredVertex(ColorG,PointB);
	ColoredVertex(ColorB,PointC);
	//ƽ��acd
	ColoredVertex(ColorR,PointA);
	ColoredVertex(ColorB,PointC);
	ColoredVertex(ColorY,PointD);
	//ƽ��abc
	ColoredVertex(ColorB,PointC);
	ColoredVertex(ColorG,PointB);
	ColoredVertex(ColorY,PointD);
	//ƽ��abc
	ColoredVertex(ColorG,PointB);
	ColoredVertex(ColorR,PointA);
	ColoredVertex(ColorB,PointC);
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glEndList();

	}		//��������ʾ�б�
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();					//��ͼ����ϵ��ջ�����Լ����Ϊ��������λ�ͼʱ���ʵ���ʼλ��
	glRotatef(angle,0,1,0);
	glCallList(list);
	glPopMatrix();		 //��ͼ����ϵ��ջ����ص��˸ղŵĻ�ͼ��ʼλ��
	glutSwapBuffers();

}
void myIdle(void)
{
	angle+=0.3;
	if( angle >= 360.0f )
		angle = 0.0f;
	Display();
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("123");
	glutDisplayFunc(&Display);
	glutIdleFunc(&myIdle);
	glutMainLoop();
}