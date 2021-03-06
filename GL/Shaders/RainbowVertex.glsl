#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out vec3 vNormal; 
out vec3 vView;
out vec3 vModel;

uniform mat4 world, view, proj;
uniform vec3 eyePos;
        
void main()
{
    vModel = aPos;
    gl_Position = proj * view * world * vec4(aPos, 1.0f);
    vNormal = normalize(transpose(inverse(mat3(world))) * aNorm);
    vec3 worldPos = (world * vec4(aPos, 1.0)).xyz;
    vView = normalize(eyePos - worldPos);
}