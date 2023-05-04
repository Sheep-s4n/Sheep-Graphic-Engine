#pragma once
#include <vector>
#include "object.h"
#include <map>
#include <iostream>
#include <memory>
#include <GLEW/glew.h>
#include <stdarg.h>
#include <FreeType/freetype.h>

class Program;

template <class T>
class Animator : private Object // all the member from Object become private in Animator
{
private:
	struct TextureInfo
	{
		int sloat;
		std::string image_path;
	};
	T* shape;
	std::map<int, TextureInfo> myMap;
	int next_texture_sloat_available;
	int current_texture_sloat;
	int frame_count;
	bool has_frame = false;
public:
	Animator(T* _shape) : shape(_shape), frame_count(99999), next_texture_sloat_available(0), current_texture_sloat(0)
	{
		Program::sub_objects.push_back(this);
		shape->Texture = "";
	};
	~Animator()
	{
		std::cout << "deleted animator" << std::endl;
	}
	void linkShape(T* _shape)
	{
		shape = _shape;
	};
	void nextFrame(int switch_interval)
	{
		if (shape->Texture != "") return; // not changing if the shape has already a texture
		frame_count++;
		if (frame_count <= switch_interval) return;
		frame_count = 0;
		if (current_texture_sloat > myMap.size() - 1) current_texture_sloat = 0;
		int max_it = 32;
		while (myMap.count(current_texture_sloat) < 1 || myMap[current_texture_sloat].sloat == -1) {
			current_texture_sloat++;
			if (current_texture_sloat > myMap.size() - 1) current_texture_sloat = 0;
			if (--max_it < 1) return;
		}
		shape->setTexture(myMap[current_texture_sloat].image_path, "c_texture", true, myMap[current_texture_sloat].sloat);
		current_texture_sloat++;
	};
	void removeFrame(int _sloat)
	{
		myMap[_sloat].sloat = -1;
	}
	void removeFrame(std::string image_path)
	{
		int key = 0;
		for (auto it = myMap.begin(); it != myMap.end(); it++) {
			if (it->second.image_path == image_path) {
				key = it->first;
				break;
			};
		};
		myMap[key].sloat = -1;
	}
	void restoreFrame(int _sloat)
	{
		myMap[_sloat].sloat = _sloat;
	}
	void nextFrameReverseOrder(int switch_interval)
	{
		if (shape->Texture != "") return;
		frame_count++;
		if (frame_count <= switch_interval) return;
		frame_count = 0;
		if (current_texture_sloat < 0) current_texture_sloat = myMap.size() - 1;
		int max_it = 32;
		while (myMap.count(current_texture_sloat) < 1 || myMap[current_texture_sloat].image_path == "") {
			current_texture_sloat--;
			if (++max_it < 1) break;
		}
		shape->setTexture(myMap[current_texture_sloat].image_path, "c_texture", true, myMap[current_texture_sloat].sloat);
		current_texture_sloat--;
	};
	void addFrames(int count, ...)
	{
		va_list args; // Define a variable argument list object
		va_start(args, count); // Initialize the variable argument list with the last named argument

		std::string* arr = new std::string[count];
		for (int i = 0; i < count; i++) 
		{
			arr[i] = va_arg(args, const char*); // Retrieve the next argument from the variable argument list and store it in the array
		}

		va_end(args); // Clean up the variable argument list

		// Now you can use the array 'arr' inside the function
		for (int i = 0; i < count; i++) 
		{
			addFrame(arr[i]);
		}
		delete[] arr;
	}
	void addFrame(std::string image_path)
	{
		if (!has_frame) 
		{
			shape->setUniform1b("has_texture", true);
			has_frame = true;
		}
		shape->setTexture(image_path, "c_texture", true, next_texture_sloat_available);
		myMap.insert({ next_texture_sloat_available , {next_texture_sloat_available , image_path} });
		next_texture_sloat_available++;
	};

	void draw() {};
};

class Text {
private :
	FT_Face face;
	FT_Library ft;
	Shader fs = Shader("F_text.shader" , GL_FRAGMENT_SHADER);
	Shader vs = Shader("V_text.shader" , GL_VERTEX_SHADER , fs.getProgram());
	unsigned int VAO;
	unsigned int VBO;
public:
	void draw();
	void setSizes(int X, int Y);
	void setSizes(int XY);
	void scaleL(int scaler);
	Text();
	~Text();
	int scale;
	int font_size;
	int X;
	int Y;
	std::string value;
	std::string font_file;
	std::string font_path;
};


class Program {
public:
	void renderShapes();
	inline static std::vector<Object*> sub_objects;
	inline static std::vector<Text*> sub_texts;
	void onStartup();
	void onUpdate();
	void onFinish();
	void clearObjects();
};

