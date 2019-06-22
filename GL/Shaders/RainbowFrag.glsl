#version 330 core

in vec3 vNormal; 
in vec3 vView;
in vec3 vModel;

out vec4 FragColor;

uniform vec3 matDiff, matSpec, matAmbi, matEmis;
uniform vec3 srcDiff, srcSpec, srcAmbi;
uniform vec3 lightDir;
uniform float shininess;
uniform float alpha;
uniform float modelWidth;

vec3 Rainbow( in float xval )
{
   vec3 rainbowColour;
   float transV = (1.0 / modelWidth) * xval + 0.5;

   if(transV < 0.0)
   {
      rainbowColour = vec3(0.0, 0.0, 0.0);
   } 
   else if (transV >= 0.0 && transV < 0.2)
   {
      rainbowColour = vec3(0.5 * (1.0 - transV / 0.2), 0.0, 0.5 + 0.5 * transV / 0.2);
   } 
   else if(transV >= 0.2 && transV < 0.4)
   {
      rainbowColour = vec3(0.0, (transV - 0.2) * 5.0, 1.0);
   }
   else if(transV >= 0.4 && transV < 0.6)
   {
      rainbowColour = vec3(0.0, 1.0, (0.6 - transV) * 5.0);
   }
   else if(transV >= 0.6 && transV < 0.8)
   {
      rainbowColour = vec3((transV - 0.6) * 5.0, 1.0, 0.0);
   }
   else if(transV >= 0.8 && transV < 1.0)
   {
      rainbowColour = vec3(1.0, (1.0 - transV) * 5.0, 0.0);
   }
   else
   {
      rainbowColour = vec3(1.0, 1.0, 1.0);
   }

   return rainbowColour;
}

void main()
{

   vec3 normal = normalize(vNormal);
   vec3 view = normalize(vView);
   vec3 light = normalize(lightDir);
   vec3 rColour = Rainbow(vModel.x);

   vec3 diff = max(dot(normal, light), 0.0) * rColour;
   vec3 refl = 2.0 * normal * dot(normal, light) - light;
   vec3 spec = pow(max(dot(refl, view), 0.0), shininess) * srcSpec * matSpec;
   vec3 ambi = srcAmbi * rColour;
   
   FragColor = vec4(clamp(diff + spec + ambi, 0.0, 1.0), 1.0);
}