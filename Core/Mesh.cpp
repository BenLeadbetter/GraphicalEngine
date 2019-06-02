/**
 *  Source file for the Mesh class header
*/

#include "Mesh.hpp"
#include "ObjLoader.h"
#include <cmath>

ObjectData getMeshData(const std::string& filename)
{
    ObjLoader loader(filename);

    return loader.getData();
}

std::unique_ptr<Mesh> Mesh::createMesh(MeshID meshID)
{
    std::unique_ptr<Mesh> ret = nullptr;

    switch(meshID)
    {
        case MeshID::CUBE:
            ret = std::unique_ptr<Mesh>(new Cube);
            break;
        
        case MeshID::SPHERE:
            ret = std::unique_ptr<Mesh>(new Sphere);
            break;
        
        case MeshID::ICOSAHEDRON:
            ret = std::unique_ptr<Mesh>(new Icosahedron);
            break;
        
        case MeshID::TUBE:
            ret = std::unique_ptr<Mesh>(new Tube);
            break;
        
        case MeshID::SPANNER:
            ret = std::unique_ptr<Mesh>(new Spanner);
            break;
    }

    return ret;
}

ObjectData Sphere::createObjectData()
{
    return getMeshData("MeshFiles/Sphere.obj");
}


ObjectData Cube::createObjectData()
{
    return getMeshData("MeshFiles/Cube.obj");
}


ObjectData Icosahedron::createObjectData()
{
    return getMeshData("MeshFiles/Icosahedron.obj");
}

ObjectData Tube::createObjectData()
{
    return getMeshData("MeshFiles/Tube.obj");
}

ObjectData Spanner::createObjectData()
{
    return getMeshData("MeshFiles/Spanner.obj");
}

