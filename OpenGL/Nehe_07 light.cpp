#include <gl/glut.h>
#define WIDTH 400
#define HEIGHT 400
static GLfloat angle = 0.0f;
void myDisplay(void)
{
	glClearColor(0.5,0.5,0.6,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

			// 创建透视效果视图
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 40.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 10, 15, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			// 定义太阳光源，它是一种白色的光源
	{
	GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_light_diffuse[] = {0.0f, 0.0f, 0.0f, 0.5f};
	GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	}
		// 定义太阳的材质并绘制太阳
	{
	GLfloat sun_mat_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_diffuse[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);
	glutSolidSphere(3.0, 40, 32);
	}
		// 定义地球的材质并绘制地球
	{
	GLfloat earth_mat_ambient[] = {0.0f, 1.0f, 0.1f, 1.0f};
	GLfloat earth_mat_diffuse[] = {0.0f, 1.0f, 0.2f, 1.0f};
	GLfloat earth_mat_specular[] = {0.0f, 1.0f, 1.0f, 1.0f};
	GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat earth_mat_shininess = 40.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(8.0f, 0.0f, 0.0f);
	glutSolidSphere(2.0, 40, 32);
	}
	glutSwapBuffers();
}
void myIdle(void)
{
	angle += 1.0f;
	if( angle >= 360.0f )
		angle = 0.0f;
	myDisplay();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL 光照演示");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	glutMainLoop();
	return 0;
}