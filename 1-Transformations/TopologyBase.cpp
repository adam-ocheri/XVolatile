#include "TopologyBase.h"


TopologyBase::TopologyBase()
{
    CreateTriangle();
}

TopologyBase::TopologyBase(size_t Location)
{
    AttributePointer_LayoutLocation = Location;
    CreateTriangle();
}

// Define and Create Triangle topology 
void TopologyBase::CreateTriangle()
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
    glVertexAttribPointer(AttributePointer_LayoutLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // Enable attributes and link the vertex data with a `Layout Location`
    glEnableVertexAttribArray(AttributePointer_LayoutLocation);

    // Unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbined the vertex data
    glBindVertexArray(0);
}