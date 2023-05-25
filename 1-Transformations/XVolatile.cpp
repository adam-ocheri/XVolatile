// XVolatile.cpp : This file contains the 'main' function. Program execution begins and ends here.

#pragma once

#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "WindowManager.h"
#include "ShaderManager.h"
#include "ShaderBase.h"
#include "Renderer.h"


int main()
{
    WindowManager* MainWindow = new WindowManager();
    if (!MainWindow) return 1;

    Renderer* RendererV1 = new Renderer();

    // Main Loop - Looping as long as the window is open
    while (MainWindow->GetIsWindowOpen())
    {
        // Get & Handle user events
        glfwPollEvents();

        // Clear the screen color buffer and set overlay color
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Renderer->Render();
        RendererV1->Render();

        // Replace the previous frame's scene and render the updated scene | RENDER CYCLE END
        glfwSwapBuffers(MainWindow->GetWindow());
    }

    return 0;
}


