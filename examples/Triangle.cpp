#ifdef _MSC_VER
#include <windows.h>
#endif
#ifdef _MSC_VER
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <GL/glfx.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _MSC_VER
#include "VisualStudioDebugOutput.h"
VisualStudioDebugOutput debug_buffer(true,NULL,128);
#endif

#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"opengl32.lib")
using namespace std;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argCount, char** szArgList)
{
    GLFWwindow* window;
	
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640,480,"Simple example",NULL,NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
	GLenum glewres=glewInit();
    if (!glewres)
        exit(EXIT_FAILURE);
	GLuint empty_vao=0;
	glGenVertexArrays(1,&empty_vao);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
	int effect=glfxGenEffect();
	glfxParseEffectFromFile(effect,"../../examples/Effect.sfx",NULL,NULL,NULL);

	// Make the texture:
    while(!glfwWindowShouldClose(window))
    {
		int width=1,height=1;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width/(float)height;
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

		glfxApply(effect,0);
		
	// GL Insists on having a bound vertex array object, even if we're not using it in the vertex shader.
	glBindVertexArray(empty_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); 
	
		glfxUnapply(effect);
        glBegin(GL_TRIANGLES);
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(-0.6f,-0.4f,0.0f);
			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(0.6f,-0.4f,0.0f);
			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(0.0f,0.6f,0.0f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	glDeleteVertexArrays(1, &empty_vao);
	glfxDeleteEffect(effect);
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

//! [code]
