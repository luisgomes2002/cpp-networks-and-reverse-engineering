#pragma once

unsigned int createShaderProgram(
	const char *vertexSource,
	const char *fragmentSource);

void destroyShaderProgram(unsigned int program);
