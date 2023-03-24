#include "VertexArray.h"
#include <iostream>
#include <GLEW/glew.h>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
};

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &vertexArray);
	std::cout << "deleted vertex vertexArray" << std::endl;
}

void VertexArray::bind() {
	glBindVertexArray(vertexArray);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}

unsigned int VertexArray::getVertexArray() {
	return vertexArray;
}

/* 
	unsigned int vertexArray;
	glGenVertexArrays(1, &vertexArray); // creating a vertex array
	glBindVertexArray(vertexArray); // binding vertex array
*/
