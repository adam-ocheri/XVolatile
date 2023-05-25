#include "TopologyBase.h"

size_t TopologyBase::LayoutLocation = -1;

TopologyBase::TopologyBase()
{
    AttributePointer_LayoutLocation = ++LayoutLocation;

    Vertices = {};

    Vertices.push_back(Vector3(-1.0f, -1.0f, 0.0f));
    Vertices.push_back(Vector3(1.0f, -1.0f, 0.0f));
    Vertices.push_back(Vector3(0.0f, 1.0f, 0.0f));   
}

TopologyBase::TopologyBase(size_t Location) 
{
    AttributePointer_LayoutLocation = ++LayoutLocation;

    Vertices = {};

    Vertices.push_back(Vector3(-1.0f, -1.0f, 0.0f));
    Vertices.push_back(Vector3(1.0f, -1.0f, 0.0f));
    Vertices.push_back(Vector3(0.0f, 1.0f, 0.0f));

    //CreateTopology();
}

TopologyBase::TopologyBase(std::vector<Vector3> VertexData) : Vertices(VertexData)
{
    AttributePointer_LayoutLocation = ++LayoutLocation;
}

TopologyBase::TopologyBase(size_t Location, std::vector<Vector3> VertexData) : Vertices(VertexData)
{
    AttributePointer_LayoutLocation = ++LayoutLocation;
}

// Define and Create Triangle topology 
void TopologyBase::CreateTopology()
{

    const int vertexCount = Vertices.size() * 3;

    GLfloat* VertexData = new GLfloat[vertexCount];

    for (int i{}; i < Vertices.size(); ++i)
    {
        VertexData[i * 3] =  Vertices.at(i).X ;
        VertexData[i * 3 + 1] =  Vertices.at(i).Y ;
        VertexData[i * 3 + 2] =  Vertices.at(i).Z ;
    }

    // Generate a vertex array, store it in the VAO, and bind it
    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);

    // Generate buffer, store it in the VBO, and bind it
    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);

    // Allocate storage for the buffer to pass the vertex array position data
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Vertices.size() * 3, VertexData, GL_STATIC_DRAW);
    // Define the layout and settings of the vertex data
    glVertexAttribPointer(AttributePointer_LayoutLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // Enable attributes and link the vertex data with a `Layout Location`
    glEnableVertexAttribArray(AttributePointer_LayoutLocation);

    // Unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbined the vertex data
    glBindVertexArray(0);
}