#include "rendering/opengl_renderer.hpp"
#include "rendering/cube_renderer.hpp"
#include "rendering/shader_program.hpp"

#include <stdexcept>

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

OpenGLRenderer::OpenGLRenderer(int width, int height)
	: width(width), height(height)
{
	initializeWindow();
	configureOpenGL();
}

void OpenGLRenderer::initializeWindow()
{
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW.");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(
		width,
		height,
		"Click the blue button to spawn the cube",
		nullptr,
		nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create the OpenGL window.");
	}
}

void OpenGLRenderer::configureOpenGL()
{
	glfwMakeContextCurrent(window);
	if (gladLoadGL(glfwGetProcAddress) == 0)
	{
		throw std::runtime_error("Failed to load OpenGL functions.");
	}

	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	createRenderResources();
}

OpenGLRenderer::~OpenGLRenderer()
{
	destroyRenderResources();

	if (window != nullptr)
	{
		glfwDestroyWindow(window);
	}

	glfwTerminate();
}

bool OpenGLRenderer::isOpen() const
{
	return window != nullptr && !glfwWindowShouldClose(window);
}

bool OpenGLRenderer::isKeyPressed(Key key) const
{
	int glfwKey = GLFW_KEY_UNKNOWN;

	switch (key)
	{
	case Key::Escape:
		glfwKey = GLFW_KEY_ESCAPE;
		break;
	}

	return glfwGetKey(window, glfwKey) == GLFW_PRESS;
}

bool OpenGLRenderer::isMouseButtonPressed(MouseButton button) const
{
	int glfwButton = GLFW_MOUSE_BUTTON_LEFT;

	switch (button)
	{
	case MouseButton::Left:
		glfwButton = GLFW_MOUSE_BUTTON_LEFT;
		break;
	}

	return glfwGetMouseButton(window, glfwButton) == GLFW_PRESS;
}

void OpenGLRenderer::getMousePosition(double &x, double &y) const
{
	glfwGetCursorPos(window, &x, &y);
}

Camera &OpenGLRenderer::getCamera()
{
	return camera;
}

void OpenGLRenderer::beginFrame()
{
	glfwPollEvents();

	int framebufferWidth;
	int framebufferHeight;
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);
	clearFrame();
}

void OpenGLRenderer::createRenderResources()
{
	const char *vertexShader = R"(
		#version 330 core
		layout (location = 0) in vec3 aPosition;
		uniform mat4 uMvp;
		void main() { gl_Position = uMvp * vec4(aPosition, 1.0); }
	)";
	const char *fragmentShader = R"(
		#version 330 core
		out vec4 fragmentColor;
		uniform vec3 uColor;
		void main() { fragmentColor = vec4(uColor, 1.0); }
	)";

	shaderProgram = createShaderProgram(vertexShader, fragmentShader);
	cubeMesh.initialize();
	rectangleMesh.initialize();
}

void OpenGLRenderer::destroyRenderResources()
{
	if (window == nullptr)
	{
		return;
	}

	cubeMesh.destroy();
	rectangleMesh.destroy();
	destroyShaderProgram(shaderProgram);
	shaderProgram = 0;
}

Mat4 OpenGLRenderer::getViewMatrix() const
{
	Vec3 inversePosition = {
		-camera.position.x,
		-camera.position.y,
		-camera.position.z};
	return multiply(rotationX(camera.pitch), translation(inversePosition));
}

void OpenGLRenderer::clearFrame() const
{
	glClearColor(0.30f, 0.45f, 0.65f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::setShaderColor(const Vec3 &color) const
{
	int location = glGetUniformLocation(shaderProgram, "uColor");
	glUniform3f(location, color.x, color.y, color.z);
}

void OpenGLRenderer::setShaderMvp(const Mat4 &mvp) const
{
	int location = glGetUniformLocation(shaderProgram, "uMvp");
	glUniformMatrix4fv(location, 1, GL_FALSE, mvp.values);
}

void OpenGLRenderer::draw(const GameObject &object) const
{
	const CubeRenderer *cube = object.getComponent<CubeRenderer>();
	if (cube == nullptr || !cube->visible)
	{
		return;
	}

	const float aspect = static_cast<float>(width) / height;
	const Mat4 projection = perspective(55.0f, aspect, 1.0f, 2500.0f);
	const Vec3 center = {
		object.position.x + cube->size.x / 2.0f,
		object.position.y + cube->size.y / 2.0f,
		object.position.z + cube->size.z / 2.0f};
	const Mat4 model = multiply(translation(center), scale(cube->size));
	const Mat4 mvp = multiply(projection, multiply(getViewMatrix(), model));

	glUseProgram(shaderProgram);
	setShaderMvp(mvp);
	setShaderColor(cube->color);
	cubeMesh.draw();
}

void OpenGLRenderer::drawButton(
	int x,
	int y,
	int buttonWidth,
	int buttonHeight,
	bool highlighted) const
{
	glDisable(GL_DEPTH_TEST);
	const Mat4 projection = orthographic(0.0f, static_cast<float>(width),
		static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	const Vec3 center = {
		x + buttonWidth / 2.0f,
		y + buttonHeight / 2.0f,
		0.0f};
	const Mat4 model = multiply(translation(center),
		scale({static_cast<float>(buttonWidth), static_cast<float>(buttonHeight), 1.0f}));

	glUseProgram(shaderProgram);
	setShaderMvp(multiply(projection, model));
	setShaderColor(highlighted
		? Vec3{0.20f, 0.55f, 1.0f}
		: Vec3{0.10f, 0.35f, 0.80f});
	rectangleMesh.draw();
	glEnable(GL_DEPTH_TEST);
}

void OpenGLRenderer::endFrame()
{
	glfwSwapBuffers(window);
}
