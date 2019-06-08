#version 330 core

in vec3 vNormal, vView;

out vec4 FragColor;

uniform vec3 matDiff, matSpec, matAmbi, matEmis;
uniform vec3 srcDiff, srcSpec, srcAmbi;
uniform float shininess;
uniform float alpha;
uniform vec3 lightDir;


void main()
{
   
   FragColor = vec4(matDiff, 1.0f);
}