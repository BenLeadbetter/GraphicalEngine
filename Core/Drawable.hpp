#ifndef GUARD_DRAWABLE_HPP
#define GUARD_DRAWABLE_HPP

/*
*   Header file for the Drawable class
*/

#include "BufferData.hpp"
#include "../Maths/Matrix4.hpp"
#include <memory>
#include <array>

enum class RenderMode {LINE, FILL};

struct DrawData
{
    unsigned int VertexArrayID;
    unsigned int VertexBufferID;
    unsigned int ElementBufferID;
    unsigned int NumberOfIndices;
    RenderMode renderMode;
    Matrix4 WorldTransform = Matrix4(1.0);
};

class Drawable
{
    public:
        
        //
        Drawable();
        Drawable(std::shared_ptr<BufferData> dataPtr);
        virtual ~Drawable();
        Drawable(const Drawable&);
        Drawable& operator=(const Drawable&);
        
        //
        std::array<float, 4> getColor() const;
        DrawData getDrawData() const;
        bool isActive() const; 
        void setMesh(std::shared_ptr<BufferData> dataPtr);
        void setColor(const float&, const float&, const float&, const float&);
        void setRenderMode(RenderMode mode);


        // orientation
        void setPosition(const Vector3&);
        void displace(const Vector3&);
        Vector3 getPosition() const;
        void scale(const float &);

    private:

        //
        std::array<float, 4> Color;
        Matrix4 transform;
        bool active;
        std::shared_ptr<BufferData> GLdata;
        RenderMode renderMode;
};

#endif