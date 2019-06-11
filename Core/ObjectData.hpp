#ifndef GUARD_OBJECT_DATA_HPP
#define GUARD_OBJECT_DATA_HPP

/*
*       Header file for the object data struct
*/

#include <vector>
#include <array>

struct ObjectData
{
    using Vector = std::array<float, 3>;
    using VertexData = std::array<unsigned int, 3>;
    using FaceData = std::array<VertexData, 3>;

    std::vector<Vector> vertices;
    std::vector<Vector> normals;
    std::vector<FaceData> faceData;
};


#endif