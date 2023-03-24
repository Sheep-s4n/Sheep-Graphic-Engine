#pragma once
#include <vector>
#include "object.h"
#include<iostream>
#include <GLFW/glfw3.h>


class Camera {
private:
	inline static glm::vec3 transformMatrice;
	inline static float increment;
	inline static bool right;
	inline static bool left;
	inline static bool up;
	inline static bool down;
	inline static std::string uniform;
	inline static std::vector<Object*> objects;
	inline static void resetPosition();
	inline static void setPositionBool(bool& pos, int& action , int& key , int mykey);
	inline static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	inline static void set_uniforms();
public:
	Camera();
	Camera(float inc , std::string uniform_n);
	void addObjectToCamera(Object* obj);
	void setIncrement(float inc);
	void setUniformName(std::string uniform_n);
	void setCameraPosition(GLFWwindow* window);
};
