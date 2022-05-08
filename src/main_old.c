#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include "renderer.h"

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000

const uint32_t window_flags = SDL_WINDOW_OPENGL;

unsigned int compile_shaders()
{
	// vertex shader
	const char* vertex_shader_src = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"}\0";

	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
	glCompileShader(vertex_shader);


	// error checking
	{
		int success;
		char info_log[512];
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
			printf("Vertex Shader comilation failed\n%s\n", info_log);
			return 1;
		}
	}

	// fragment shader
	const char* fragment_shader_src =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
	glCompileShader(fragment_shader);

	// error checking
	{
		int success;
		char info_log[512];
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
			printf("Fragment Shader comilation failed\n%s\n", info_log);
			return 1;
		}
	}

	// shader program
	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	// error checking
	{
		int success;
		char info_log[512];
		glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader_program, 512, NULL, info_log);
			printf("program failed to link\n%s\n", info_log);
			return 0;
		}
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}

int main(int ArgCount, char** Args)
{
	if (!renderer_init("Godfeels", 1000, 1000, window_flags))
		return 1;

	bool run = true;
	bool fullscreen = false;

	unsigned int shader_program = compile_shaders();

	// Bottom left
	const float tri_1[] = {
		-1.0, 0.0, 0.0,
		-1.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
	};

	// top right
	const float tri_2[] = {
		1.0, 1.0, 0.0,
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	};
	unsigned int VAO_1;
	glGenVertexArrays(1, &VAO_1);
	glBindVertexArray(VAO_1);

	unsigned int VBO_1;
	glGenBuffers(1, &VBO_1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri_1), tri_1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	unsigned int VAO_2;
	glGenVertexArrays(2, &VAO_2);
	glBindVertexArray(VAO_2);

	unsigned int VBO_2;
	glGenBuffers(1, &VBO_2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri_2), tri_2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	while (run)
	{
		SDL_Event Event;
		while (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_KEYDOWN)
			{
				switch (Event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					run = 0;
					break;
				case 'f':
					fullscreen = !fullscreen;
					if (fullscreen)
						SDL_SetWindowFullscreen(window, window_flags | SDL_WINDOW_FULLSCREEN_DESKTOP);
					else
						SDL_SetWindowFullscreen(window, window_flags);
					break;
				default:
					break;
				}
			}
			else if (Event.type == SDL_QUIT)
			{
				run = 0;
			}
		}
		glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUseProgram(shader_program);
		glBindVertexArray(VAO_1);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glBindVertexArray(VAO_2);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		SDL_GL_SwapWindow(window);
	}

	glDeleteVertexArrays(1, &VAO_1);
	glDeleteBuffers(1, &VBO_1);
	glDeleteVertexArrays(1, &VAO_2);
	glDeleteBuffers(1, &VBO_2);
	glDeleteProgram(shader_program);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}