#version 330 core

in vec3 vNormal; 
in vec3 vView;

out vec4 FragColor;

uniform vec3 matDiff, matSpec, matAmbi, matEmis;
uniform vec3 srcDiff, srcSpec, srcAmbi;
uniform vec3 lightDir;
uniform float shininess;
uniform float alpha;

void main()
{
   vec3 normal = normalize(vNormal);
   vec3 view = normalize(vView);
   vec3 light = normalize(lightDir);

   vec3 diff = max(dot(normal, light), 0.0) * matDiff;

   vec3 refl = 2.0 * normal * dot(normal, light) - light;
   vec3 spec = pow(max(dot(refl, view), 0.0), shininess) * srcSpec * matSpec;

   vec3 ambi = srcAmbi * matAmbi;
   
   FragColor = vec4(diff, 1.0);
}