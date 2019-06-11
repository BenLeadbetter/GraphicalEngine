#include "ObjLoader.h"
#include "ObjectData.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <array>

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

void advanceToNextDigit(std::string::iterator& itr)
{
    while(!std::isdigit(*itr))
        ++itr;
}

void advanceToNextSlash(std::string::iterator& itr)
{
    ++itr;
    
    while(*itr != '/')
        ++itr;
}

void appendNextVector(
    std::vector<ObjectData::Vector>& data, 
    std::string::iterator itr
    )
{
    ObjectData::Vector vec;

    vec[0] = nextFloat(itr);
    advancePastNextValue(itr);
    vec[1] = nextFloat(itr);
    advancePastNextValue(itr);
    vec[2] = nextFloat(itr);

    data.push_back(vec);
}


void loadFaceVertexDataToArray(std::array<unsigned int, 3>& arr, std::string::iterator itr)
{
    advanceToNextDigit(itr);
    arr[0] = nextInt(itr);
    
    advanceToNextSlash(itr);
    if(std::isdigit(*(itr + 1)))
        arr[1] = nextInt(itr);
    
    advanceToNextSlash(itr);
    if(std::isdigit(*(itr + 1)))
        arr[2] = nextInt(itr);
}

#include<iostream>

void ObjLoader::loadVertices()
{
    static std::string vertexFlag = "v ";
    auto itr = search(file.begin(), file.end(), vertexFlag.begin(), vertexFlag.end());

    while(itr != file.end())
    {
        advanceToNextWhiteSpace(itr);
        appendNextVector(data.vertices, itr);
        itr = search(itr, file.end(), vertexFlag.begin(), vertexFlag.end());
    }

    // print to see contents
    std::cout << "Vertices:" << std::endl;
    for(auto itr = data.vertices.begin(); itr != data.vertices.end(); ++itr)
    {
        std:: cout << (*itr)[0] << ", " <<
        (*itr)[1] << ", " <<
        (*itr)[2] << std::endl;
    }
}

void ObjLoader::loadNormals()
{
    static std::string normalFlag = "vn";
    auto itr = search(file.begin(), file.end(), normalFlag.begin(), normalFlag.end());

    while(itr != file.end())
    {
        advanceToNextWhiteSpace(itr);
        appendNextVector(data.normals, itr);
        itr = search(++itr, file.end(), normalFlag.begin(), normalFlag.end());
    }


    // print to see contents
    std::cout << "Normals:" << std::endl;
    for(auto itr = data.normals.begin(); itr != data.normals.end(); ++itr)
    {
        std:: cout << (*itr)[0] << ", " <<
        (*itr)[1] << ", " <<
        (*itr)[2] << std::endl;
    }
}

void ObjLoader::loadFaceData()
{
    static std::string faceFlag = "f ";
    auto itr = search(file.begin(), file.end(), faceFlag.begin(), faceFlag.end());

    while(itr != file.end())
    {
        ObjectData::FaceData currentFaceData;

        for(int i = 0; i != 3; ++i)
        {
            ObjectData::VertexData currentVertexData;
            
            advanceToNextDigit(itr);
            loadFaceVertexDataToArray(currentVertexData, itr);
            currentFaceData[i] = currentVertexData;
            advanceToNextWhiteSpace(itr);
        }

        data.faceData.push_back(currentFaceData);

        itr = search(itr, file.end(), faceFlag.begin(), faceFlag.end());
    }

    // print to see contents
    std::cout << "faceData contains:" << std::endl;
    for(auto itr = data.faceData.begin(); itr != data.faceData.end(); ++itr)
    {
        for(int i = 0; i != 3; ++i)
        {  
            std::cout << (*itr)[i][0] << "/" <<
            (*itr)[i][1] << "/" <<
            (*itr)[i][2] << "\t";        
        }

        std::cout << std::endl;
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
    loadFaceData();
}

ObjectData& ObjLoader::getData()
{
    return data;
}