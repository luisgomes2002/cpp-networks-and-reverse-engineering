#include "rendering/shader_program.hpp"

#include <stdexcept>
#include <string>

#include <glad/gl.h>

namespace
{
unsigned int compileShader(unsigned int type, const char *source)
{
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int succeeded;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &succeeded);
	if (succeeded == GL_TRUE)
	{
		return shader;
	}

	char message[512];
	glGetShaderInfoLog(shader, sizeof(message), nullptr, message);
	glDeleteShader(shader);
	throw std::runtime_error(std::string("Shader compilation failed: ") + message);
}
}

unsigned int createShaderProgram(
	const char *vertexSource,
	const char *fragmentSource)
{
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	int succeeded;
	glGetProgramiv(program, GL_LINK_STATUS, &succeeded);
	if (succeeded == GL_TRUE)
	{
		return program;
	}

	char message[512];
	glGetProgramInfoLog(program, sizeof(message), nullptr, message);
	glDeleteProgram(program);
	throw std::runtime_error(std::string("Shader linking failed: ") + message);
}

void destroyShaderProgram(unsigned int program)
{
	if (program != 0)
	{
		glDeleteProgram(program);
	}
}
