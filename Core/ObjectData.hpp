#ifndef GUARD_OBJECT_DATA_HPP
#define GUARD_OBJECT_DATA_HPP

/*
*       Header file for the object data struct
*/

#include <vector>

struct ObjectData
{
    using VertexData = std::array<unsigned int, 3>;
    using FaceData = std::array<VertexData, 3>;

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<FaceData> faceData;
};


#endif