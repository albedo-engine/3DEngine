#version 330 core

out vec4 FragColor;
in vec3 vTexCoords;

uniform samplerCube uCubeMap;

void main()
{
    FragColor = texture(uCubeMap, normalize(vTexCoords));
}