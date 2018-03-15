#include<windows.h>
#include<gl/gl.h>
#include<gl/glut.h>
HGLRC hRC=NULL;
HDC hDC=NULL;
HWND hWnd=NULL;
HINSTANCE hInstance;

bool keys[256];
bool active=TRUE;
bool fullscreen=TRUE;

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

GLvoid ReSizeCLScence(GLsizei width,GLsizei height);
{
	if(height==0)
	{
		height=1;
	}
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	return TRUE;
}

