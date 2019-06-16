#include "BufferData.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void BufferData::createVertexArray()
{
    glGenVertexArrays(1, &VertexArrayID);
    glCheckError();
}

void BufferData::enablePositionAttribPointer()
{
    glBindVertexArray(VertexArrayID);
    glVertexAttribPointer(
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        6 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    glCheckError();
}

void BufferData::enableNormalAttribPointer()
{
    glBindVertexArray(VertexArrayID);
    glVertexAttribPointer(
        1, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    glCheckError();
}

void BufferData::releaseAllBuffers()
{
    glDeleteBuffers(1, &VertexBufferID);

    glCheckError();
}

void BufferData::deleteVertexArray()
{
    glDeleteVertexArrays(1, &VertexArrayID);

    glCheckError();
}

BufferData::~BufferData()
{
    releaseAllBuffers();
    deleteVertexArray();
}

unsigned int BufferData::getVertexArrayID() const
{
    return VertexArrayID;
}

unsigned int BufferData::getVertexBufferID() const
{
    return VertexBufferID;
}

unsigned int BufferData::getNumberOfVertices() const
{
    return NumberOfVertices;
}


void BUFFER_DATA_appendVertexData(
    const ObjectData::VertexData& vertexData, 
    const ObjectData& objectData, 
    std::vector<float>& data)
{
    data.push_back(objectData.vertices[vertexData[0] - 1][0]);
    data.push_back(objectData.vertices[vertexData[0] - 1][1]);
    data.push_back(objectData.vertices[vertexData[0] - 1][2]);
    data.push_back(objectData.normals[vertexData[2] - 1][0]);
    data.push_back(objectData.normals[vertexData[2] - 1][1]);
    data.push_back(objectData.normals[vertexData[2]  -1][2]);
}

void BUFFER_DATA_appendFaceData(
    const ObjectData::FaceData& faceData, 
    const ObjectData& objectData,
    std::vector<float>& data)
{
    for(int i = 0; i != 3; ++i)
        BUFFER_DATA_appendVertexData(faceData[i], objectData, data);
}