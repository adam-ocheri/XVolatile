// XVolatile.cpp : This file contains the 'main' function. Program execution begins and ends here.

#pragma once

#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "WindowManager.h"
#include "ShaderManager.h"

// Window size
const GLint WIDTH = 800;
const GLint HEIGHT = 600;

// Each object we draw will need to have it's own VAO, VBO and ShaderProgram
GLuint VertexArrayObject, VertexBufferObject, ShaderProgram;



// Provide basic generic testing for Shaders / Shader Programs
bool VerifyIsValid(GLuint ShaderProgram, GLenum StatusType)
{
    // Determine test type
    const bool Compiling = StatusType == GL_COMPILE_STATUS;

    // Define internal data storage for status and logs
    static GLchar Log[1024] = { 0 };
    GLint Result = 0;

    // Get validity status from Program/Shader
    Compiling ?
        glGetShaderiv(ShaderProgram, StatusType, &Result)
        :
        glGetProgramiv(ShaderProgram, StatusType, &Result)
        ;
    if (!Result)
    {
        // Get error info logs 
        Compiling ?
            glGetShaderInfoLog(ShaderProgram, sizeof(Log), NULL, Log)
            :
            glGetProgramInfoLog(ShaderProgram, sizeof(Log), NULL, Log)
            ;
        printf("Shader creation of %d type FAILED! \n Log Info: \n %s", StatusType, Log);

        // Test Failure
        return false;
    }
    else {
        // Test Success
        return true;
    }
}

// Instantiate a single Shader Pass
void CreateShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType)
{
    // Instantite a new Shader
    GLuint Shader = glCreateShader(ShaderType);

    // Get reference to the code of the Shader, and store it's length 
    const GLchar* Code[1];
    Code[0] = ShaderCode;

    GLint CodeLength[1];
    CodeLength[0] = strlen(ShaderCode);

    /*
    Assign the code to the newly Instantiated shader, 
    and allocate memory in storage according to the code's length
    */ 
    glShaderSource(Shader, 1, Code, CodeLength);

    // Compile the shader
    glCompileShader(Shader);

    // Verify the shader has compiled
    VerifyIsValid(Shader, GL_COMPILE_STATUS);

    //If compiled sucessfully, the shader still has to be attached to the OpenGL context
    glAttachShader(ShaderProgram, Shader);

    //glDetachShader(ShaderProgram, Shader);
}

// Create a new shader program and compile it's individual components
void CompileShaders()
{
    // Initialize a new Shader Program
    ShaderProgram = glCreateProgram();

    if (!ShaderProgram) {
        printf("Shader program creation FAILED!");
        return;
    }

    // Instantiate the Vertex & Pixel Shaders
    //CreateShader(ShaderProgram, VertexShader, GL_VERTEX_SHADER);
    //CreateShader(ShaderProgram, PixelShader, GL_FRAGMENT_SHADER);

    // Link the program with the GPU, and verify LINK is valid
    glLinkProgram(ShaderProgram);
    VerifyIsValid(ShaderProgram, GL_LINK_STATUS);
    
    // Validate the program, and verify VALIDATE is valid
    glValidateProgram(ShaderProgram);
    VerifyIsValid(ShaderProgram, GL_VALIDATE_STATUS);
}

// Define and Create Triangle topology 
void CreateTriangle()
{
    // Define vertices positioning
    GLfloat Vertices[] = {
        -1.0f, -1.0f, 0.0f,     //Vertex #1
        1.0f, -1.0f, 0.0f,      //Vertex #2
        0.0f, 1.0f, 0.0f        //Vertex #3
    };

    // Generate a vertex array, store it in the VAO, and bind it
    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);

        // Generate buffer, store it in the VBO, and bind it
        glGenBuffers(1, &VertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);

            // Allocate storage for the buffer to pass the vertex array position data
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, Vertices, GL_STATIC_DRAW);
            // Define the layout and settings of the vertex data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            // Enable attributes and link the vertex data with a `Layout Location`
            glEnableVertexAttribArray(0);

        // Unbind the buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbined the vertex data
    glBindVertexArray(0);
}

int main()
{

    WindowManager* MainWindow = new WindowManager();

    if (!MainWindow) return 1;

    ShaderManager* Renderer = new ShaderManager();

    //ShaderManager* ShaderManager = new ShaderManager();

    // Initialize Scene rendering
    //CreateTriangle();
    //CompileShaders();

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


