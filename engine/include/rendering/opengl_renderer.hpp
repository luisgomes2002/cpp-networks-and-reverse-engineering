#pragma once

#include "core/gameobject.hpp"
#include "core/mat4.hpp"
#include "rendering/camera.hpp"
#include "rendering/primitives/cube_mesh.hpp"
#include "rendering/primitives/rectangle_mesh.hpp"

enum class Key
{
	Escape
};

enum class MouseButton
{
	Left
};

struct GLFWwindow;

class OpenGLRenderer
{
public:
	OpenGLRenderer(int width, int height);
	~OpenGLRenderer();

	OpenGLRenderer(const OpenGLRenderer &) = delete;
	OpenGLRenderer &operator=(const OpenGLRenderer &) = delete;

	bool isOpen() const;
	bool isKeyPressed(Key key) const;
	bool isMouseButtonPressed(MouseButton button) const;
	void getMousePosition(double &x, double &y) const;
	Camera &getCamera();

	void beginFrame();
	void draw(const GameObject &object) const;
	void drawButton(int x, int y, int width, int height, bool highlighted) const;
	void endFrame();

private:
	void initializeWindow();
	void configureOpenGL();
	void createRenderResources();
	void destroyRenderResources();
	void clearFrame() const;
	Mat4 getViewMatrix() const;
	void setShaderColor(const Vec3 &color) const;
	void setShaderMvp(const Mat4 &mvp) const;

	GLFWwindow *window = nullptr;
	int width;
	int height;
	Camera camera;
	unsigned int shaderProgram = 0;
	CubeMesh cubeMesh;
	RectangleMesh rectangleMesh;
};
