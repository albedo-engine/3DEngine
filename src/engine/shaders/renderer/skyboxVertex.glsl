#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 vTexCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * vec4(position, 1.0f);
    vTexCoords = position;
}