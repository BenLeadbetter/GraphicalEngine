
/*
*       Source file for the Drawable class
*/

#include "Drawable.hpp"



Drawable::Drawable():
    transform(Matrix4(1.0f)),
    GLdata(nullptr),
    renderMode(RenderMode::LINE)
{};

Drawable::Drawable(std::shared_ptr<BufferData> dataPtr):
    transform(Matrix4(1.0f)),
    GLdata(dataPtr),
    renderMode(RenderMode::LINE)
{};


Drawable::~Drawable()
{};

Drawable::Drawable(const Drawable& drawable):
transform(Matrix4(drawable.transform))
{
    colorData = drawable.colorData;
    renderMode = drawable.renderMode;
    GLdata = drawable.GLdata;

}

Drawable& Drawable::operator=(const Drawable& rhs)
{
    // replace the simple data
    colorData = rhs.colorData;
    renderMode = rhs.renderMode;
    GLdata = rhs.GLdata;

    return *this;
}

// interface
ObjectColorData Drawable::getColorData() const
{
    return colorData;
}

void Drawable::setMesh(std::shared_ptr<BufferData> DataPtr)
{
    GLdata = DataPtr;
}

void Drawable::setColorData(const ObjectColorData& data)
{
    colorData = data;
}

void Drawable::setRenderMode(RenderMode mode)
{
    renderMode = mode;   
}

DrawData Drawable::getDrawData() const
{
    DrawData ret;
    ret.VertexArrayID = GLdata->getVertexArrayID();
    ret.VertexBufferID = GLdata->getVertexBufferID();
    ret.NumberOfIndices = GLdata->getNumberOfIndices();
    ret.renderMode = renderMode;
    ret.WorldTransform = transform;

    return ret;
}

// orientation
void Drawable::setPosition(const Vector3& pos)
{
    transform.setEntry(0, 3, pos.x());
    transform.setEntry(1, 3, pos.y());
    transform.setEntry(2, 3, pos.z());
}

void Drawable::displace(const Vector3& vec)
{
    transform.setEntry(0, 3, transform.getEntry(0, 3) + vec.x());
    transform.setEntry(1, 3, transform.getEntry(1, 3) + vec.y());
    transform.setEntry(2, 3, transform.getEntry(2, 3) + vec.z());    
}

Vector3 Drawable::getPosition() const
{
    Vector4 pos = transform.getCol(3);

    return Vector3 (pos.x(), pos.y(), pos.x());
}

void Drawable::scale(const float& scalar)
{
    Matrix4 scalingMatrix {
        (float)scalar, 0.0f,   0.0f,   0.0f,
        0.0f,   (float)scalar, 0.0f,   0.0f,
        0.0f,   0.0f,   (float)scalar, 0.0f,
        0.0f,   0.0f,   0.0f,   1.0f 
    };

    transform *= scalingMatrix;
}
