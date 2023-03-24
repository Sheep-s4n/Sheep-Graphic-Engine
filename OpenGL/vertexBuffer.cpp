#include "vertexBuffer.h"
#include <iostream>
#include <GLEW/glew.h>

VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
};

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &buffer);
	std::cout << "deleted vertex buffer" << std::endl;
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(float arr[], int arrSize, int drawType) {
	glBufferData(GL_ARRAY_BUFFER,arrSize , arr, drawType);
}

void VertexBuffer::layout(int index, int vertexCount, int stride, int begin) {
	glVertexAttribPointer(index, vertexCount, GL_FLOAT, GL_FALSE, stride, (GLvoid*)begin);
	glEnableVertexAttribArray(index);
}

unsigned int VertexBuffer::getVertexBuffer() {
	return buffer;
}

/*
original code :

unsigned int bufferID;
  //          number of buffer , pointer to buffer id
  glGenBuffers(1, &bufferID); // creating a buffer
  //          how to buffer is used , bufferID
  glBindBuffer(GL_ARRAY_BUFFER, bufferID); // binding a buffer = selecting a buffer = all futur openg GL function call aply to this buffer
  //      how to buffer is used, size of data , data , how data will be used
  glBufferData(GL_ARRAY_BUFFER, sizeof(data) , data , GL_STATIC_DRAW);
  //GL_DYNAMIC_DRAW = will be rendered every frame and get changed
  //GL_STATIC_DRAW = will be rendered every frame and not changed

	  // index , type count of vertecises , type , vertices size in bits , first component offset
	glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, sizeof(float) * 2 , 0); // adding vertex attribute
	glEnableVertexAttribArray(0); // enabling vertex attribute at index  0
  */