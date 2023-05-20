// XVolatile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800;
const GLint HEIGHT = 600;

int main()
{
    //Initialise GLFW and verify it
    if (!glfwInit())
    {
        printf("Initialisation Error!");
        glfwTerminate();
        return 1;
    }

    //todo Setup GLFW window properties
    //OpenGL Version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Force depcrated code below this version to NOT compile - CORE_PROFILE == No Backwards Compatability
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Allow backwards campatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //todo Create GLFW window
    GLFWwindow* MainWindow = glfwCreateWindow(WIDTH, HEIGHT, "XVolatile", NULL, NULL);
    if (!MainWindow)
    {
        printf("Window Initialisation Error!");
        glfwTerminate();
        return 1;
    }
    //Set Buffer Size information
    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(MainWindow, &BufferWidth, &BufferHeight);
    //Set up Context for GLEW to use
    glfwMakeContextCurrent(MainWindow);
    //Enable Experimental features
    glewExperimental = GLFW_TRUE;

    //todo Create GLEW Context
    if (glewInit() != GLEW_OK)
    {
        printf("Glew Initialisation Error!");
        glfwDestroyWindow(MainWindow);
        glfwTerminate();
        return 1;
    }

    //todo Setup viewport Size
    glViewport(0, 0, BufferWidth, BufferHeight);

    //todo Main Loop
    //Looping as long as the window is open
    while (!glfwWindowShouldClose(MainWindow))
    {
        // Get & Handle user events
        glfwPollEvents();

        //Clear the screen color buffer and set overlay color
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Replace the previous frame's scene and render the updated scene 
        glfwSwapBuffers(MainWindow);
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
