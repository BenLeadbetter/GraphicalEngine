#ifndef GUARD__OBJ_LOADER_H
#define GUARD__OBJ_LOADER_H

#include "ObjectData.hpp"
#include <string>

class ObjLoader
{
    public:
        ObjLoader(const std::string filename);
        bool loadFile(const std::string& filename);
        ObjectData& getData();

    private:
        void loadVertices();
        void loadNormals();
        void loadFaceData();

    private:
        ObjectData data;
        std::string file;
};


#endif
