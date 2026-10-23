#pragma once

class RectangleMesh
{
public:
	void initialize();
	void destroy();
	void draw() const;

private:
	unsigned int vertexArray = 0;
	unsigned int vertexBuffer = 0;
};
