#version 330 core

//layout (location = 0) out vec3 position;
layout (location = 0) out vec3 normal;
layout (location = 1) out vec4 albedo; // RGB: diffuse, A: spec

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D uAlbedoMap;
uniform vec4 uAlbedoFactor;

void main()
{
  //position = FragPos;
  normal = normalize(Normal);
  //albedo.rgb = vec3(0,1,1); // Diffuse
  albedo.rgba = texture2D(uAlbedoMap, TexCoords); // Diffuse
  //albedo.rgba = uAlbedoFactor; // Diffuse
  //albedo.a = 1; // Specular
}