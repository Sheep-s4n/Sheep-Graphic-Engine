#pragma once

class IndexBuffer {
private:
	unsigned int buffer;
public:
	IndexBuffer();
	~IndexBuffer();
	void bind();
	void unbind();
	void setData(unsigned int arr[], int arrSize, int drawType);
	unsigned int getBuffer();
};
