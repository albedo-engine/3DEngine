#include <GL/gl.h>
static const GLchar *shader_source_deferred_vs[] = {
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 normal;\n"
    "layout (location = 2) in vec2 texCoords;\n"
    "out vec2 TexCoords;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(position, 1.0f);\n"
    "    TexCoords = texCoords;\n"
    "}\n"
};
