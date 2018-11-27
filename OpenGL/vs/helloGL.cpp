#include <iostream>
#define GL_STATIC
#include "GLFW/glfw3.h"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    return 0;
}
/*
const GLuint NumVertice = 6;
GLuint Buffers[Numbuffers];

void init(void){
    static const GLfloat vertices[NumVertices][2] =
    {
        {-0.9, -0.9},
        {0.85, -0.9},
        {-0.9, 0.85},
        {0.9, -0.85},
        {0.9, 0.9},
        {-0.85, 0.9}
    };

    glCreatBuffers(NumBuffers, Buffers);
}

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
*/
