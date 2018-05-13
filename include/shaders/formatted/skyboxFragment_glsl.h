#include <GL/gl.h>
static const GLchar *shader_source_skyboxFragment_glsl[] = {
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 vTexCoords;\n"
    "uniform samplerCube uCubeMap;\n"
    "void main()\n"
    "{\n"
    "    FragColor = texture(uCubeMap, normalize(vTexCoords));\n"
    "}\n"
};
