#include <GL/gl.h>
static const GLchar *shader_source_skyboxVertex_glsl[] = {
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 normal;\n"
    "layout (location = 2) in vec2 texCoords;\n"
    "out vec3 vTexCoords;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = projection * view * vec4(position, 1.0f);\n"
    "    vTexCoords = position;\n"
    "}\n"
};
