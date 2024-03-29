#pragma once
#include <GLEW/glew.h>

class VertexBuffer {
public:
	unsigned int buffer;
	VertexBuffer();
	~VertexBuffer();
	void bind();
	void unbind();
	void setData(float arr[], int arrSize, int drawType);
	void layout(int index, int vertexCount, int stride, int begin = 0);
	unsigned int getVertexBuffer();
};
