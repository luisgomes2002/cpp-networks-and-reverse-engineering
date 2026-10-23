#include "systems/game.hpp"

#include "rendering/cube_renderer.hpp"
#include "rendering/opengl_renderer.hpp"
#include "core/gameobject.hpp"

void run()
{
	OpenGLRenderer renderer(800, 600);
	renderer.getCamera().position = {0.0f, 80.0f, 240.0f};

	GameObject cubeObject("cube", {-16.0f, 0.0f, 0.0f});
	CubeRenderer &cube = cubeObject.addComponent<CubeRenderer>();
	cube.color = {0.2f, 0.8f, 0.3f};
	cube.size = {32.0f, 32.0f, 32.0f};

	const int buttonX = 24;
	const int buttonY = 24;
	const int buttonWidth = 220;
	const int buttonHeight = 64;
	bool cubeVisible = false;
	bool wasMousePressed = false;

	while (renderer.isOpen() && !renderer.isKeyPressed(Key::Escape))
	{
		renderer.beginFrame();

		double mouseX;
		double mouseY;
		renderer.getMousePosition(mouseX, mouseY);

		bool isOverButton =
			mouseX >= buttonX && mouseX <= buttonX + buttonWidth &&
			mouseY >= buttonY && mouseY <= buttonY + buttonHeight;
		renderer.drawButton(buttonX, buttonY, buttonWidth, buttonHeight, isOverButton);

		bool isMousePressed = renderer.isMouseButtonPressed(MouseButton::Left);
		if (isMousePressed && !wasMousePressed && isOverButton)
		{
			cubeVisible = true;
		}
		wasMousePressed = isMousePressed;

		if (cubeVisible)
		{
			renderer.draw(cubeObject);
		}

		renderer.endFrame();
	}
}
