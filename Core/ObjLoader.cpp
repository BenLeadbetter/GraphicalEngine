#include "ObjLoader.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

bool isFloatChar(const char ch)
{
    return std::isdigit(ch) || ch == '.' || ch == '-';
}

float nextFloat(std::string::iterator itr)
{
    auto itr1 = itr;

    while(!isFloatChar(*itr1))
        ++itr1;

    auto itr2 = itr1;

    while(isFloatChar(*itr2))
        ++itr2;
    
    return std::stof(std::string(itr1, itr2));
}

unsigned int nextInt(std::string::iterator itr)
{
    auto itr1 = itr;

    while(!isdigit(*itr1))
        ++itr1;
    
    auto itr2 = itr1;

    while(isdigit(*itr2))
        ++itr2;
    
    return std::stoi(std::string(itr1, itr2));
}

void advancePastNextValue(std::string::iterator& itr)
{
    while(!isFloatChar(*itr))
        ++itr;
    
    while(isFloatChar(*itr))
        ++itr;
}

void advanceToNextWhiteSpace(std::string::iterator& itr)
{
    ++itr;
    while(!isspace(*itr))
        ++itr;
}

void loadThreeFloatsIntoVector(
    std::vector<float>& vec, 
    std::string::iterator itr
    )
{
    for(int i = 0; i != 3; ++i)
    {
        vec.push_back(nextFloat(itr));
        advancePastNextValue(itr);
    }
}

void loadThreeIntsIntoVector(
    std::vector<unsigned int>& vec,
    std::string::iterator itr
    )
{
    for(int i = 0; i != 3; ++i)
    {
        vec.push_back(nextInt(itr) - 1);
        advanceToNextWhiteSpace(itr);
    }
}

void ObjLoader::loadVertices()
{
    auto itr = find(file.begin(), file.end(), 'v');

    while(itr != file.end())
    {
        advanceToNextWhiteSpace(itr);
        loadThreeFloatsIntoVector(data.vertices, itr);
        itr = find(++itr, file.end(), 'v');
    }
}

void ObjLoader::loadNormals()
{
    static std::string normalFlag = "vn";
    auto itr = search(file.begin(), file.end(), normalFlag.begin(), normalFlag.end());

    while(itr != file.end())
    {
        advanceToNextWhiteSpace(itr);
        loadThreeFloatsIntoVector(data.normals, itr);
        itr = search(++itr, file.end(), normalFlag.begin(), normalFlag.end());
    }
}

void ObjLoader::loadIndices()
{
    static std::string faceFlag = "f ";
    auto itr = search(file.begin(), file.end(), faceFlag.begin(), faceFlag.end());

    while(itr != file.end())
    {
        advanceToNextWhiteSpace(itr);
        loadThreeIntsIntoVector(data.indices, itr);
        itr = search(++itr, file.end(), faceFlag.begin(), faceFlag.end());
    }

}

bool ObjLoader::loadFile(const std::string& filename)
{
    std::ifstream fstream(filename);
    if(!fstream.is_open())
    {
        std::cout << "Could not open file: " << filename << std::endl;
        return false;
    }
    
    std::string line;
    while(std::getline(fstream, line))
        file += line;
    
    fstream.close();

    return true;
}

ObjLoader::ObjLoader(const std::string filename)
{
    loadFile(filename);
    loadVertices();
    loadNormals();
    loadIndices();
}

ObjectData& ObjLoader::getData()
{
    return data;
}