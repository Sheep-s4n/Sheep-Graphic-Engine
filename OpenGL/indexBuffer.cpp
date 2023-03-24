#include "indexBuffer.h"
#include <iostream>
#include <GLEW/glew.h>

IndexBuffer::IndexBuffer() {
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
};

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &buffer);
	std::cout << "deleted vertex buffer" << std::endl;
}

void IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::setData(unsigned int arr[], int arrSize, int drawType) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arrSize, arr, drawType);
}

unsigned int IndexBuffer::getBuffer() {
	return buffer;
}

/*
original code:

// unsigned int index_buffer_id;// index buffer =  using vertex index to avoid repeating the same vertex
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
*/