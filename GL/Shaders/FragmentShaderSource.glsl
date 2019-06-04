#version 330 core

in vec3 vNormal, vView;

out vec4 FragColor;

uniform vec3 matDiff, matSpec, matAmbi, matEmit;
uniform vec3 srcDiff, srcSpec, srcAmbi;
uniform float shininess;
uniform vec3 lightDir;


void main()
{
   
   FragColor = objectColor;
}