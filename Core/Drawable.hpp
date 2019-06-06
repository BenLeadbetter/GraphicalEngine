#ifndef GUARD_DRAWABLE_HPP
#define GUARD_DRAWABLE_HPP

/*
*   Header file for the Drawable class
*/

#include "BufferData.hpp"
#include "../Maths/Matrix4.hpp"
#include "../Maths/Vector4.hpp"
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

class ObjectColorData
{
    public:
        ObjectColorData() {};
        template<typename Vec, typename Sh>
        ObjectColorData(Vec&& vec1, Vec&& vec2, Vec&& vec3, Vec&& vec4, Sh sh):
        diffuse(std::forward<Vec>(vec1)),
        specular(std::forward<Vec>(vec2)),
        emissive(std::forward<Vec>(vec3)),
        ambient(std::forward<Vec>(vec4)),
        shininess(std::forward<Sh>(sh))
        {};

        void setDiffuse(const Vector4& vec) { diffuse = vec; }
        void setSpecular(const Vector4& vec) { specular = vec; }
        void setEmissive(const Vector4& vec) { emissive = vec; }
        void setAmbient(const Vector4& vec) { ambient = vec; }

        Vector4 getDiffuse() const { return diffuse; }
        Vector4 getSpecular() const { return specular; }
        Vector4 getEmissive() const { return emissive; }
        Vector4 getAmbient() const { return ambient; }
        
    private:
        Vector4 diffuse = Vector4({1.0f, 1.0f, 1.0f, 1.0f});
        Vector4 specular = Vector4({0.5f, 0.5f, 0.5f, 1.0f});
        Vector4 emissive = Vector4({0.0f, 0.0f, 0.0f, 0.0f});
        Vector4 ambient = Vector4({1.0f, 1.0f, 1.0f, 1.0f});
        float shininess = 1.0f;
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
        ObjectColorData getColorData() const;
        DrawData getDrawData() const;
        void setMesh(std::shared_ptr<BufferData> dataPtr);
        void setColorData(const ObjectColorData&);
        void setRenderMode(RenderMode mode);


        // orientation
        void setPosition(const Vector3&);
        void displace(const Vector3&);
        Vector3 getPosition() const;
        void scale(const float &);

    private:

        //
        ObjectColorData colorData;
        Matrix4 transform;
        std::shared_ptr<BufferData> GLdata;
        RenderMode renderMode;
};

#endif