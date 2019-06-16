#ifndef GUARD_SHADER_H
#define GUARD_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include "../Maths/Matrix4.hpp"

class Shader 
{
    public:
        unsigned int ID;
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

        void use();

        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMat4(const std::string& name, Matrix4& value) const;
        void setMat4(const std::string& name, glm::mat4 value) const;
        void setVec4(const std::string& name, const Vector4& vec) const;
        void setVec3(const std::string& name, const Vector3& vec);
        void setVec2(const std::string& name, const Vector2& vec);
};

#endif