#pragma once
#include <string>
#include "abstraction.h"
#include <unordered_map>
#include <memory>
#include <vector>

class Object {
protected :
	int point_count;
	VertexArray vertexArray;
	IndexBuffer S_indexBuffer;
	VertexBuffer S_vertexBuffer;
	IndexBuffer D_indexBuffer;
	VertexBuffer D_vertexBuffer;
	Texture texture;
	std::unordered_map<std::string, int> uniforms;
	bool is_using_dynamic_buffer;
	bool vertex_buffer_is_set;
	bool index_buffer_is_set;
public:
	unsigned int program_id;
	virtual ~Object();
	Object();
	void bind();
	void unbind();
	unsigned int getProgram();
	void setStaticIndexBuffer(unsigned int arr[], int arrSize);
	void setStaticVertexBuffer(float arr[], int arrSize);
	void setDynamicVertexBuffer(float arr[], int arrSize);
	void setDynamicIndexBuffer(unsigned int arr[], int arrSize);
	void setVertexBufferLayout(int index, int vertexCount, int stride, int begin=0);
	void setShader(const std::string path, const unsigned int shaderType);
	void setTexture(const std::string path ,std::string name , bool flipImage, int slot = 0);
	void setUniform1f(std::string name, float value);
	void setUniform1b(std::string name, bool value);
	void setUniform1i(std::string name, int value);
	void setUniformMatrix4fv(std::string name, glm::mat4& first_value);
	void setUniform2f(std::string name, float value1, float value2);
	void setUniform4f(std::string name, float value1, float value2, float value3, float value4);
	int getTextureSlot(std::string path);
	int getUniformID(std::string& name);
	Texture* getTextureI();
	int Z_index;
	void virtual draw();
};

