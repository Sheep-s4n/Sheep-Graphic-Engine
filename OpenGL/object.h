#pragma once
#include <string>
#include "abstraction.h"
#include <unordered_map>
#include <memory>
#include <vector>


struct Texture_colors
{
	int R;
	int G;
	int B;
	int A;
};

class Object {
friend class Camera;
protected :

	int prev_X;
	int prev_Y;
	int prev_Z_index;
	int prev_colors[4];
	int prev_texture_colors[4];
	int prev_rotation[3];
	std::string prev_Texture;
	glm::mat4 proj;
	void updateTexture();
	void updateColors();
	void updateRotation();
	void updateTextureColors();
	bool colorChanged();
	bool rotationChanged();
	bool textureColorsChanged();


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
	unsigned int program_id;
	void bind();
	void unbind();
	unsigned int getProgram();
	void setStaticIndexBuffer(unsigned int arr[], int arrSize);
	void setStaticVertexBuffer(float arr[], int arrSize);
	void setDynamicVertexBuffer(float arr[], int arrSize);
	void setDynamicIndexBuffer(unsigned int arr[], int arrSize);
	void setVertexBufferLayout(int index, int vertexCount, int stride, int begin = 0);
	void setShader(const std::string path, const unsigned int shaderType);
	void setUniform1f(std::string name, float value);
	void setUniform1i(std::string name, int value);
	void setUniform2f(std::string name, float value1, float value2);
	void setUniform4f(std::string name, float value1, float value2, float value3, float value4);
	void setUniformMatrix4fv(std::string name, glm::mat4& first_value);
	int getTextureSlot(std::string path);
	int getUniformID(std::string& name);
	void draw(int mode);
	void drawFromVBO(int coord_count);
	void drawFromVBO(int coord_count , int mode);
	Texture* getTextureI();

public:
	virtual ~Object();
	Object();
	
	void setUniform1b(std::string name, bool value);
	void setTexture(const std::string path, std::string name, bool flipImage, int slot = 0);
	void removeTexture();
	void setColors(int RGB);
	void setColors(int R, int G, int B);
	void setColors(int R, int G, int B, int A);
	void setColorsTexture(int RGB);
	void setColorsTexture(int R, int G, int B);
	void setColorsTexture(int R, int G, int B, int A);
	void setPositions(int XY);
	void setPositions(int X, int Y);
	void setPositions(int X, int Y, int Z);
	void setRotation(int Z);
	void setRotations(int X, int Y, int Z);
	virtual void draw();
	int R;
	int G;
	int B;
	int A;
	int X;
	int Y;
	int X_rotate;
	int Y_rotate;
	int Z_rotate;
	int Z_index;
	bool Transform_from_middle;
	std::string Texture;
	Texture_colors Texture_colors;
};

