#version 330 core

precision lowp float;

in vec3 vNormal; 
in vec3 vView;
in vec4 vWorld;

out vec4 FragColor;

uniform vec3 matDiff, matSpec, matAmbi, matEmis;
uniform vec3 srcDiff, srcSpec, srcAmbi;
uniform vec3 lightDir;
uniform float shininess;
uniform float alpha;

const vec3 SPOTLIGHTPOS = vec3(0.0, 12, 12);
const vec3 SPOTLIGHTTARGET = vec3(0.5, 0.0, 0.0);
const float SPOTAPERTURE = 0.01;
const float FUZZ_WIDTH = 0.2;
const vec3 SPOTCOLOR = vec3(1.0, 0.0, 0.0);

void AddSpotlight(out vec4 totalIntensity, in vec3 position, in vec3 target, in vec3 color)
{
   vec3 spotlightDir = normalize(target - position);
   float DiffuseFactor = max(dot(spotlightDir, vNormal), 0.0);

   float angleSine = length(cross(spotlightDir, vWorld.xyz - position));
   float cutoffSine = tan(SPOTAPERTURE) * length(target - position);
   float BlendFactor = smoothstep(cutoffSine - FUZZ_WIDTH, cutoffSine + FUZZ_WIDTH, angleSine);

   totalIntensity += clamp(vec4(BlendFactor * DiffuseFactor * color, 1.0), 0.0, 1.0);
}

void main()
{
   vec3 normal = normalize(vNormal);
   vec3 view = normalize(vView);
   vec3 light = normalize(lightDir);

   float diff = max(dot(normal, light), 0.0);
   vec3 refl = 2.0 * normal * dot(normal, light) - light;
   vec3 spec = pow(max(dot(refl, view), 0.0), shininess) * srcSpec;
   vec3 ambi = srcAmbi * matAmbi;
   
   FragColor = vec4(0.0, 0.0, 0.0, 1.0);

   AddSpotlight(FragColor, SPOTLIGHTPOS, SPOTLIGHTTARGET, SPOTCOLOR);
}