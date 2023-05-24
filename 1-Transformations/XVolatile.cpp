// XVolatile.cpp : This file contains the 'main' function. Program execution begins and ends here.

#pragma once

#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "WindowManager.h"
#include "ShaderManager.h"
#include "ShaderBase.h"


int main()
{
    WindowManager* MainWindow = new WindowManager();
    if (!MainWindow) return 1;

    ShaderManager* Renderer = new ShaderManager();
    if (!Renderer) return 1;

    ShaderBase* Shader = new ShaderBase(Vector4(1.0f, 1.0f, 0.0f, 1.0f), Vector4(0.3f, 0.3f, 0.3f, 1.0f));
    //ShaderBase* Shader = new ShaderBase();
    if (!Shader) return 1;

    //Renderer->GatherResources(Shader->ShaderProgram, Shader->VertexShader.c_str(), Shader->PixelShader.c_str());
    Renderer->GatherResources(Shader);

    Renderer->CreateTriangle();

    Renderer->CompileShaders();
    

    // Main Loop - Looping as long as the window is open
    while (MainWindow->GetIsWindowOpen())
    {
        // Get & Handle user events
        glfwPollEvents();

        // Clear the screen color buffer and set overlay color
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Renderer->Render();

        // Replace the previous frame's scene and render the updated scene | RENDER CYCLE END
        glfwSwapBuffers(MainWindow->GetWindow());
    }

    return 0;
}


