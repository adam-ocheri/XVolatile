#pragma once

#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class WindowManager
{
private:
	const GLint WIDTH = 800;
	const GLint HEIGHT = 600;
	GLFWwindow* MainWindow;
public:
	WindowManager();
	~WindowManager();
	GLFWwindow* GetWindow() const;
	int GetIsWindowOpen() const;
};

