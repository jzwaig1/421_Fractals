#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <thread>

void line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	/* Loop until the user closes the window */

	int frameCount = 1;
	bool drawSwitch = true;
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		if (frameCount % 50 == 0)
			drawSwitch = !drawSwitch;

		glLineWidth(2.5);
		glColor3f(1.0, 0.0, 0.0);

		if (drawSwitch) {
			
			line(0, 0, 0, 15);
		}
		else {
			line(0, 0, 15, 0);
		}
		frameCount++;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

