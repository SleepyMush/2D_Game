#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

struct WindowSettings
{
	int width;
	int height;
};

class Windows {
private:
	GLFWwindow* window;
public:
	Windows() : window(nullptr) {};
	operator GLFWwindow* () const {
		return window;
	}

	int CreateWindow(int screenWidth, int screenHeight, const char* Windowname);
	~Windows();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow* window);
	static void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
};
