#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <GL/glu.h>

#include <cglm/cglm.h>

typedef GLuint Shader;
typedef GLuint ShaderProgram;

ShaderProgram shader_compile(const char* vertex_source, const char* fragment_source);
void shader_use(Shader shader);
void shader_set_matrix_4(Shader shader, const char* name, const mat4 matrix);
void shader_set_matrix_3(Shader shader, const char* name, const mat3 matrix);

#endif