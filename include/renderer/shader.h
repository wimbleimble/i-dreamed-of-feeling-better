#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <GL/glu.h>

typedef GLuint Shader;
typedef GLuint ShaderProgram;

ShaderProgram shader_compile(const char* vertex_source, const char* fragment_source);

#endif