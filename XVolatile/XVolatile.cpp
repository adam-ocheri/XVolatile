// XVolatile.cpp : This file contains the 'main' function. Program execution begins and ends here.
//


#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800;
const GLint HEIGHT = 600;

//Each object we draw will need to have it's own VAO, VBO and Shaders
GLuint VertexArrayObject, VertexBufferObject, ShaderProgram;

static const char* VertexShader = "                                 \n\
#version 330                                                        \n\
                                                                    \n\
layout (location = 0) in vec3 pos;                                 \n\
                                                                    \n\
void main()                                                         \n\
{                                                                   \n\
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);                   \n\
}";

static const char* PixelShader = "                                  \n\
#version 330                                                        \n\
                                                                    \n\
out vec4 color;                                                     \n\
                                                                    \n\
void main()                                                         \n\
{                                                                   \n\
    color = vec4(1.0, 0.0, 0.0, 1.0);                               \n\
}";

void CreateShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType)
{
    GLuint Shader = glCreateShader(ShaderType);

    const GLchar* Code[1];
    Code[0] = ShaderCode;

    GLint CodeLength[1];
    CodeLength[0] = strlen(ShaderCode);

    glShaderSource(Shader, 1, Code, CodeLength);
    glCompileShader(Shader);

    //Verify Compilation
    GLint Result = 0;
    GLchar Logs[1024] = { 0 };

    glGetShaderiv(Shader, GL_COMPILE_STATUS, &Result);
    if (!Result)
    {
        glGetShaderInfoLog(Shader, sizeof(Logs), NULL, Logs);
        printf("Shader Compilation FAILED! \n Log Info: \n %s", Logs);
        return;
    }

    /*
    const bool Success = ShaderErrorHandler(ShaderProgram, GL_COMPILE_STATUS, Result, Logs);

    if (!Success) {
        return;
    }
    */

    //If compiled sucessfully, the shader still has to be attached to the OpenGL context
    glAttachShader(ShaderProgram, Shader);

    //glDetachShader(ShaderProgram, Shader);
}

/*
bool ShaderErrorHandler(GLuint ShaderProgram, GLenum StatusType, GLint &Result, GLchar* Log)
{
    const bool Compiling = StatusType == GL_COMPILE_STATUS;
    const GLubyte* TestType = gluGetString(StatusType);

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, StatusType, &Result);
    if (!Result)
    {
        Compiling ? 
            glGetProgramInfoLog(ShaderProgram, sizeof(Log), NULL, Log) 
            : 
            glGetShaderInfoLog(ShaderProgram, sizeof(Log), NULL, Log)
        ;
        printf("Shader creation of %s type FAILED! \n Log Info: \n %s", TestType, Log);
        return false;
    }
    else {
        return true;
    }
}
*/

void CompileShaders()
{
    ShaderProgram = glCreateProgram();

    if (!ShaderProgram) {
        printf("Shader program creation FAILED!");
        return;
    }

    CreateShader(ShaderProgram, VertexShader, GL_VERTEX_SHADER);
    CreateShader(ShaderProgram, PixelShader, GL_FRAGMENT_SHADER);

    //todo Debugging - - - - - - - - - - - - - - - - - - - - - - - - 

    GLint Result = 0;
    GLchar Logs[1024] = { 0 };

    // Verify Shaders are Linked
    //ShaderErrorHandler(ShaderProgram, GL_LINK_STATUS, Result, Logs);
    
    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Result);
    if (!Result)
    {
        glGetProgramInfoLog(ShaderProgram, sizeof(Logs), NULL, Logs);
        printf("Shader Linking FAILED! \n Log Info: \n %s", Logs);
        return;
    }
    /**/
    // Verify Shaders are Validated
    //ShaderErrorHandler(ShaderProgram, GL_VALIDATE_STATUS, Result, Logs);
    
    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Result);
    if (!Result)
    {
        glGetProgramInfoLog(ShaderProgram, sizeof(Logs), NULL, Logs);
        printf("Shader Validation FAILED! \n Log Info: \n %s", Logs);
        return;
    }
    /**/
}

void CreateTriangle()
{
    GLfloat Vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);

    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int main()
{
    //todo Initialise GLFW and verify it
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

    //Initialize Scene rendering
    CreateTriangle();
    CompileShaders();

    //todo Main Loop
    //Looping as long as the window is open
    while (!glfwWindowShouldClose(MainWindow))
    {
        // Get & Handle user events
        glfwPollEvents();

        //Clear the screen color buffer and set overlay color
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Run the Shader program
        glUseProgram(ShaderProgram);

            glBindVertexArray(VertexArrayObject);

                glDrawArrays(GL_TRIANGLES, 0, 3);

            glBindVertexArray(0);

        glUseProgram(0);

        //Replace the previous frame's scene and render the updated scene | RENDER CYCLE END
        glfwSwapBuffers(MainWindow);
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

