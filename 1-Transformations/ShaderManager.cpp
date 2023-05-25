#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
    Shader = new ShaderBase();
}

ShaderManager::ShaderManager(ShaderBase* shader) : Shader(shader)
{
    GatherResources();
}

ShaderManager::~ShaderManager()
{
    delete Shader;
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
    GLuint ShaderInstance = glCreateShader(ShaderType);

    // Get reference to the code of the Shader, and store it's length 
    const GLchar* Code[1];
    Code[0] = ShaderCode;

    GLint CodeLength[1];
    CodeLength[0] = strlen(ShaderCode);

    /*
    Assign the code to the newly Instantiated shader,
    and allocate memory in storage according to the code's length
    */
    glShaderSource(ShaderInstance, 1, Code, CodeLength);

    // Compile the shader
    glCompileShader(ShaderInstance);

    // Verify the shader has compiled
    VerifyIsValid(ShaderInstance, GL_COMPILE_STATUS);

    //If compiled sucessfully, the shader still has to be attached to the OpenGL context
    glAttachShader(ShaderProgram, ShaderInstance);

    //glDetachShader(ShaderProgram, Shader); // At some point the shader will need to be detached - NOT here though
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
        glLinkProgram(Shader->ShaderProgram);
        VerifyIsValid(Shader->ShaderProgram, GL_LINK_STATUS);

        // Validate the program, and verify VALIDATE is valid
        glValidateProgram(Shader->ShaderProgram);
        VerifyIsValid(Shader->ShaderProgram, GL_VALIDATE_STATUS);
    }
}

void ShaderManager::CompileShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType)
{
    if (!ShaderProgram) {
        printf("Shader program INVALID!");
        return;
    }

    // Instantiate the Vertex & Pixel Shaders
    CreateShader(ShaderProgram, ShaderCode, ShaderType);
}

void ShaderManager::GatherResources()
{
    RegisterShader(Shader->ShaderProgram, Shader->VertexShader.c_str(), GL_VERTEX_SHADER);
    RegisterShader(Shader->ShaderProgram, Shader->PixelShader.c_str(), GL_FRAGMENT_SHADER);
}

void ShaderManager::GatherResources(ShaderBase* ShaderData)
{
    Shader = ShaderData;

    RegisterShader(Shader->ShaderProgram, Shader->VertexShader.c_str(), GL_VERTEX_SHADER);
    RegisterShader(Shader->ShaderProgram, Shader->PixelShader.c_str(), GL_FRAGMENT_SHADER);
}

void ShaderManager::GatherResources(GLuint shaderProgram, const char* vertexShader, const char* pixelShader)
{
    Shader->ShaderProgram = shaderProgram;
    Shader->VertexShader = vertexShader;
    Shader->PixelShader = pixelShader;

    RegisterShader(Shader->ShaderProgram, Shader->VertexShader.c_str(), GL_VERTEX_SHADER);
    RegisterShader(Shader->ShaderProgram, Shader->PixelShader.c_str(), GL_FRAGMENT_SHADER);
}

void ShaderManager::Render(GLuint VAO)
{
    // Run the Shader program
    glUseProgram(Shader->ShaderProgram);

        glBindVertexArray(VAO);

            glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

    glUseProgram(0);
}
