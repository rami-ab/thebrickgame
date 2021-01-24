#pragma once
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>


// Callback functions
void resize(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

class Window {
private:
	GLFWwindow* m_Window;
	int m_Width, m_Height;
	const char* m_Title;

public:
	Window(int width, int height, const char* title) : m_Width(width), m_Height(height), m_Title(title)
	{
		if (!init()) glfwTerminate();
	}

	bool init()
	{
		if (!glfwInit()) {
			printf("GLFW initialization failed!\n");
			return false;
		}

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

		if (!m_Window) {
			glfwTerminate();
			printf("Window creation failed!\n");
			return false;
		}

		// Context & callbacks
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowSizeCallback(m_Window, resize);

		if (glewInit() != GLEW_OK)
			printf("GLEW initialization failed!");

		printf("OpenGL version: %s\n", glGetString(GL_VERSION));
		printf("Using GLEW ver: %s\n", glGetString(GLEW_VERSION));
		
		return true;
	}

	bool isOpen() const { return !glfwWindowShouldClose(m_Window); }
	void clear()  const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	void update() {
		glfwPollEvents();
		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glfwSwapBuffers(m_Window);
	}
};