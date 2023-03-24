#pragma once

class VertexArray {
private:
	unsigned int vertexArray;
public:
	VertexArray();
	~VertexArray();
	void bind();
	void unbind();
	unsigned int getVertexArray();
};
