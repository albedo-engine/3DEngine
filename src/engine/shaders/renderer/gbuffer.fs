#version 330 core

layout (location = 0) out vec3 position;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec4 albedo; // RGB: diffuse, A: spec

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

void main()
{
  position = FragPos;
  normal = normalize(Normal);
  albedo.rgb = vec3(0,1,1); // Diffuse
  albedo.a = 1; // Specular
}