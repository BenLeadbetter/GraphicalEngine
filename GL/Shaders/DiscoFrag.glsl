#version 330 core

precision mediump float;

in vec3 vNormal; 
in vec3 vView;
in vec4 vWorld;

out vec4 FragColor;

uniform vec3 matDiff, matSpec, matAmbi, matEmis;
uniform vec3 srcDiff, srcSpec, srcAmbi;
uniform vec3 lightDir;
uniform float shininess;
uniform float alpha;
const vec3 SPOTLIGHT1POS = vec3(-5.0, -12.0, -12.0);
uniform vec3 spotlight1Target;
uniform vec3 spotlight1Color;

const vec3 SPOTLIGHT2POS = vec3(5.0, -12.0, -12.0);
uniform vec3 spotlight2Target;
uniform vec3 spotlight2Color;

const vec3 SPOTLIGHT3POS = vec3(5.0, 2.0, -12.0);
uniform vec3 spotlight3Target;
uniform vec3 spotlight3Color;

const float SPOTAPERTURE = 0.06;
const float FUZZ_WIDTH = 0.3;

vec4 Spotlight(in vec3 position, in vec3 target, in vec3 color)
{
   vec3 spotlightDir = normalize(target - position);
   float DiffuseFactor = max(dot(spotlightDir, vNormal), 0.0);

   float angleSine = length(cross(spotlightDir, vWorld.xyz - position));
   float cutoffSine = tan(SPOTAPERTURE) * length(target - position);
   float BlendFactor = 1.0 - smoothstep(cutoffSine - FUZZ_WIDTH, cutoffSine + FUZZ_WIDTH, angleSine);

   return DiffuseFactor * BlendFactor * vec4(color, 1.0);
}

void main()
{
   vec3 normal = normalize(vNormal);
   vec3 view = normalize(vView);
   vec3 light = normalize(lightDir);

   float diff = max(dot(normal, light), 0.0);
   vec3 refl = 2.0 * normal * dot(normal, light) - light;
   vec3 spec = pow(max(dot(refl, view), 0.0), shininess) * srcSpec;
   vec3 ambi = srcAmbi * matAmbi * 0.4;
   
   FragColor = 
      Spotlight(SPOTLIGHT1POS, spotlight1Target, spotlight1Color) + 
      Spotlight(SPOTLIGHT2POS, spotlight2Target, spotlight2Color) + 
      Spotlight(SPOTLIGHT3POS, spotlight3Target, spotlight3Color) +
      vec4(matDiff * srcDiff, 1.0) * diff + 
      vec4(ambi, 1.0);
}