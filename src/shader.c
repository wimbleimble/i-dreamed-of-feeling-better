#include "shader.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#define INFO_LOG_LENGTH (512)

bool shader_error_check(Shader shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char info_log[INFO_LOG_LENGTH];
		glGetShaderInfoLog(shader, INFO_LOG_LENGTH, NULL, info_log);
		printf("Shader compilation failed\n%s\n", info_log);
	}

	return success;
}

ShaderProgram shader_compile(const char* vertex_source, const char* fragment_source)
{
	Shader vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCompileShader(vertex_shader);
	assert(shader_error_check(vertex_shader));

	Shader fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	glCompileShader(fragment_shader);
	assert(shader_error_check(fragment_shader));

	ShaderProgram program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	// error checking
	{
		int success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			char info_log[INFO_LOG_LENGTH];
			glGetProgramInfoLog(program, INFO_LOG_LENGTH, NULL, info_log);
			printf("Program failed to link\n%s\n", info_log);
			assert(false && "Shader link error.");
		}
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}



