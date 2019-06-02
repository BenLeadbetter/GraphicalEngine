/**
 *  Source file for the BufferData class header
*/

#include "BufferData.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../GL/GLCheckError.hpp"
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void BufferData::createVertexArray()
{
    glGenVertexArrays(1, &VertexArrayID);
    glCheckError();
}

template<typename T>
void BufferData::createElementBuffer(T&& data)
{
    glBindVertexArray(VertexArrayID);
    glGenBuffers(1, &ElementBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferID);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(float) * data.indices.size(),
        std::forward<T>(data).indices.data(),
        GL_STATIC_DRAW
    );

    NumberOfIndices = data.indices.size();

    glCheckError();
}

template void BufferData::createElementBuffer(ObjectData&&);
template void BufferData::createElementBuffer(ObjectData&);

template<typename T>
void BufferData::createVertexBuffer(T&& data)
{
    auto vertexData = createVertexNormalVector(data.vertices, data.normals);

    glBindVertexArray(VertexArrayID);
    glGenBuffers(1, &VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(float) * 2 * data.vertices.size(), 
        vertexData.data(),
        GL_STATIC_DRAW
        );
    
    glCheckError();
}

template void BufferData::createVertexBuffer(ObjectData&& data);
template void BufferData::createVertexBuffer(ObjectData& data);

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
    glDeleteBuffers(1, &ElementBufferID);

    glCheckError();
}

void BufferData::deleteVertexArray()
{
    glDeleteVertexArrays(1, &VertexArrayID);

    glCheckError();
}

template<typename T>
BufferData::BufferData(T&& objectData)
{
    createVertexArray();
    createVertexBuffer(objectData);
    createElementBuffer(std::forward<ObjectData>(objectData));
    enablePositionAttribPointer();
    enableNormalAttribPointer();
}

template BufferData::BufferData(ObjectData&);
template BufferData::BufferData(ObjectData&&);

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

unsigned int BufferData::getElementBufferID() const
{
    return ElementBufferID;
}

unsigned int BufferData::getNumberOfIndices() const
{
    return NumberOfIndices;
}


std::vector<float> createVertexNormalVector(
    std::vector<float> verts, 
    std::vector<float> norms
    )
{
    /**
     *  Structure of VAO is
     *  vx, vy, vz, nx, ny, nz
    */

    std::vector<float> ret;
    
    for(std::vector<float>::size_type i = 0; i != verts.size(); i = i + 3)
    {
        ret.push_back(verts[i]);
        ret.push_back(verts[i + 1]);
        ret.push_back(verts[i + 2]);
        ret.push_back(norms[i]);
        ret.push_back(norms[i + 1]);
        ret.push_back(norms[i + 2]);
    }

    return ret;
}