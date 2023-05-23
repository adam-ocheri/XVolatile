#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
    //CompileShaders();
    //CreateTriangle();
}

ShaderManager::~ShaderManager()
{
    //delete[] VertexShader;
    //delete[] PixelShader;
}

// Provide basic generic testing for Shaders / Shader Programs
bool ShaderManager::VerifyIsValid(GLuint ShaderProgram, GLenum StatusType)
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

void ShaderManager::RegisterShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType)
{
    //map<GLuint, const char*, GLenum> Map(std::initializer_list<>{ ShaderProgram, ShaderCode, ShaderType });
    ShaderMaps.push_back({ {0, std::make_tuple(ShaderProgram , ShaderCode , ShaderType)} });
}

// Instantiate a single Shader Pass
void ShaderManager::CreateShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType)
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
void ShaderManager::CompileShaders()
{
    

    for (const auto& ShaderMap : ShaderMaps)
    {
        //ShaderMap.at(0);
        for (const auto& shaderMap : ShaderMap)
        {
            std::tuple<GLuint, const char*, GLenum> value = shaderMap.second;

            GLuint SP = std::get<0>(value);
            const char* Code = std::get<1>(value);
            GLenum Type = std::get<2>(value);

            CompileShader(SP, Code, Type);
        }

        // Link the program with the GPU, and verify LINK is valid
        glLinkProgram(ShaderProgram);
        VerifyIsValid(ShaderProgram, GL_LINK_STATUS);

        // Validate the program, and verify VALIDATE is valid
        glValidateProgram(ShaderProgram);
        VerifyIsValid(ShaderProgram, GL_VALIDATE_STATUS);
    }
}

void ShaderManager::CompileShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType)
{
    // Initialize a new Shader Program
    //ShaderProgram = glCreateProgram();

    if (!ShaderProgram) {
        printf("Shader program INVALID!");
        return;
    }

    // Instantiate the Vertex & Pixel Shaders
    CreateShader(ShaderProgram, ShaderCode, ShaderType);
    //CreateShader(ShaderProgram, PixelShader, GL_FRAGMENT_SHADER);

    
}

void ShaderManager::GatherResources(GLuint shaderProgram, const char* vertexShader, const char* pixelShader)
{
    ShaderProgram = shaderProgram;
    //VertexShader = vertexShader;
    //PixelShader = pixelShader;
    RegisterShader(ShaderProgram, vertexShader, GL_VERTEX_SHADER);
    RegisterShader(ShaderProgram, pixelShader, GL_FRAGMENT_SHADER);
}

void ShaderManager::GatherResources(ShaderBase* ShaderData)
{
    ShaderProgram = ShaderData->ShaderProgram;
    //VertexShader = ShaderData->VertexShader.c_str();
    //PixelShader = ShaderData->PixelShader.c_str();

    RegisterShader(ShaderProgram, ShaderData->VertexShader.c_str(), GL_VERTEX_SHADER);
    RegisterShader(ShaderProgram, ShaderData->PixelShader.c_str(), GL_FRAGMENT_SHADER);
}

void ShaderManager::Render()
{
    // Run the Shader program
    glUseProgram(ShaderProgram);

        glBindVertexArray(VertexArrayObject);

            glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

    glUseProgram(0);
}

// Define and Create Triangle topology 
void ShaderManager::CreateTriangle()
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