#ifndef GUARD_BUFFER_DATA_HPP
#define GUARD_BUFFER_DATA_HPP

#include "../GL/GLCheckError.hpp"
#define glCheckError() glCheckError_(__FILE__, __LINE__)

#include "ObjectData.hpp"

class BufferData
{
    public:
        template<typename T> BufferData(T&& objectData);
        ~BufferData();
        BufferData(const BufferData&) = delete;
        BufferData operator=(const BufferData&) = delete;

        unsigned int getVertexArrayID() const;
        unsigned int getVertexBufferID() const;
        unsigned int getNumberOfVertices() const;

    private:
        void createVertexArray();
        template<typename T> std::vector<float> vertexArrayData(T&& objectData);
        template<typename T> void createVertexBuffer(T&& objectData);
        void enablePositionAttribPointer();
        void enableNormalAttribPointer();
        void releaseAllBuffers();
        void deleteVertexArray();

    private:
        unsigned int    VertexArrayID;
        unsigned int    VertexBufferID;
        unsigned int    NumberOfVertices;
};

std::vector<float> createVertexNormalVector(std::vector<float>, std::vector<float>);

template<typename T>
BufferData::BufferData(T&& objectData)
{
    createVertexArray();
    createVertexBuffer(std::forward<T>(objectData));
    enablePositionAttribPointer();
    enableNormalAttribPointer();
}

void BUFFER_DATA_appendVertexData(
    const ObjectData::VertexData& vertexData, 
    const ObjectData& objectData, 
    std::vector<float>& data);

void BUFFER_DATA_appendFaceData(
    const ObjectData::FaceData& faceData, 
    const ObjectData& objectData,
    std::vector<float>& data);

#include <iostream>

template<typename T> 
std::vector<float> BufferData::vertexArrayData(T&& objectData)
{
    std::vector<float> data;

    for(
        auto itr = objectData.faceData.begin(); 
        itr != objectData.faceData.end(); 
        ++itr
        )
        BUFFER_DATA_appendFaceData(*itr, objectData, data);

    return data;
}

template<typename T>
void BufferData::createVertexBuffer(T&& objData)
{   
    glBindVertexArray(VertexArrayID);
    glGenBuffers(1, &VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(float) * 2 * objData.faceData.size() * 3 * 3, 
        vertexArrayData(std::forward<T>(objData)).data(),
        GL_STATIC_DRAW
        );

    NumberOfVertices = objData.faceData.size() * 3;

    glCheckError();
}

#endif
