#version 330 core

in vec3 vNormal, vView;

out vec4 FragColor;

uniform vec4 matDiff, matSpec, matAmbi, matEmis;
uniform vec4 srcDiff, srcSpec, srcAmbi;
uniform float shininess;
uniform vec3 lightDir;


void main()
{
   
   FragColor = matDiff;
}