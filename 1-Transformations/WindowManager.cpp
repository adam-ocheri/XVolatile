#include "WindowManager.h"

WindowManager::WindowManager()
{
    // Initialise GLFW and verify it
    if (!glfwInit())
    {
        printf("Initialisation Error!");
        glfwTerminate();
        return;
    }

    // Setup GLFW window properties
    //OpenGL Version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Force depcrated code below this version to NOT compile - CORE_PROFILE == No Backwards Compatability
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Allow backwards campatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create GLFW window
    MainWindow = glfwCreateWindow(WIDTH, HEIGHT, "XVolatile", NULL, NULL);

    if (!MainWindow)
    {
        printf("Window Initialisation Error!");
        glfwTerminate();
        return;
    }

    // Set Buffer Size information
    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(MainWindow, &BufferWidth, &BufferHeight);
    // Set up Context for GLEW to use
    glfwMakeContextCurrent(MainWindow);
    // Enable Experimental features
    glewExperimental = GLFW_TRUE;

    // Create GLEW Context
    if (glewInit() != GLEW_OK)
    {
        printf("Glew Initialisation Error!");
        glfwDestroyWindow(MainWindow);
        glfwTerminate();
        return;
    }

    // Setup viewport Size
    glViewport(0, 0, BufferWidth, BufferHeight);
}

WindowManager::~WindowManager()
{
    delete MainWindow;
}

GLFWwindow* WindowManager::GetWindow() const
{
    return MainWindow;
}

int WindowManager::GetIsWindowOpen() const
{
    return ~glfwWindowShouldClose(MainWindow);
}
