#pragma once
#include <vector>
#include "object.h"
#include <map>
#include <iostream>
#include <memory>
#include <GLEW/glew.h>


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
	Animator(T* _shape) : shape(_shape), frame_count(0), next_texture_sloat_available(0), current_texture_sloat(0)
	{
		Program::sub_objects.push_back(this);
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
		frame_count++;
		if (frame_count <= switch_interval) return;
		frame_count = 0;
		if (current_texture_sloat > myMap.size() - 1) current_texture_sloat = 0;
		int max_it = 32;
		while (myMap.count(current_texture_sloat) < 1) {
			current_texture_sloat++;
			if (++max_it < 1) break;
		}
		//shape->Texture = myMap[current_texture_sloat].image_path;
		int uniformLocation = glGetUniformLocation(shape->program_id, "c_texture"); // integer uniform = texture slot 
		glProgramUniform1i(shape->program_id, uniformLocation, myMap[current_texture_sloat].sloat);
		shape->setUniform1f("c_texture", (float)1.0f);
		shape->setTexture(myMap[current_texture_sloat].image_path, "c_texture", true, myMap[current_texture_sloat].sloat);
		current_texture_sloat++;
	};
	/*void removeFrame(int _sloat)
	{
		myMap.erase(_sloat);
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
		myMap.erase(key);
	}*/
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

class Program {
public:
	void renderShapes();
	inline static std::vector<Object*> sub_objects;
	void onStartup();
	void onUpdate();
	void onFinish();
	void clearObjects();
};