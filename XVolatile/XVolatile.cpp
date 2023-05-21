// XVolatile.cpp : This file contains the 'main' function. Program execution begins and ends here.



#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Window size
const GLint WIDTH = 800;
const GLint HEIGHT = 600;

// Each object we draw will need to have it's own VAO, VBO and ShaderProgram
GLuint VertexArrayObject, VertexBufferObject, ShaderProgram;

// Vertex Shader Code
static const char* VertexShader = "                                 \n\
#version 330                                                        \n\
                                                                    \n\
layout (location = 0) in vec3 pos;                                  \n\
                                                                    \n\
void main()                                                         \n\
{                                                                   \n\
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);                   \n\
}";

// Fragment Shader Code
static const char* PixelShader = "                                  \n\
#version 330                                                        \n\
                                                                    \n\
out vec4 color;                                                     \n\
                                                                    \n\
void main()                                                         \n\
{                                                                   \n\
    color = vec4(1.0, 0.0, 0.0, 1.0);                               \n\
}";

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
    CreateShader(ShaderProgram, VertexShader, GL_VERTEX_SHADER);
    CreateShader(ShaderProgram, PixelShader, GL_FRAGMENT_SHADER);

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
    GLfloat Vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
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

