#include "camera.h"


void Camera::resetPosition(){
	Camera::right = 0;
	Camera::left = 0;
	Camera::up = 0;
	Camera::down = 0;
}

Camera::Camera() {
	Camera::increment = 0.02f;
	Camera::right = false;
	Camera::left = false;
	Camera::up = false;
	Camera::down = false;
	Camera::transformMatrice.x = 0;
	Camera::transformMatrice.y = 0;
	Camera::transformMatrice.z = 0;
	Camera::uniform = "cam";
}
Camera::Camera(float inc , std::string uniform_n) {
	Camera::increment = inc;
	Camera::right = false;
	Camera::left = false;
	Camera::up = false;
	Camera::down = false;
	Camera::transformMatrice.x = 0;
	Camera::transformMatrice.y = 0;
	Camera::transformMatrice.z = 0;
	Camera::uniform = uniform_n;
}


void Camera::addObjectToCamera(Object* obj){
	Camera::objects.push_back(obj);
}

void Camera::setIncrement(float inc){
	Camera::increment = inc;
}

void Camera::setUniformName(std::string uniform_n){
	Camera::uniform = uniform_n;
}
void Camera::setPositionBool(bool& pos, int& action , int& key , int mykey) {
	if (key == mykey) {
		if (action == GLFW_PRESS) {
			pos = true;
		}
		if (action == GLFW_RELEASE) {
			pos = false;
		}
	}
}


void Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	setPositionBool(right, action,key , GLFW_KEY_RIGHT);
	setPositionBool(left, action, key, GLFW_KEY_LEFT);
	setPositionBool(up, action, key, GLFW_KEY_UP);
	setPositionBool(down, action, key, GLFW_KEY_DOWN);

}
void Camera::set_uniforms(){
	glm::mat4 camera = glm::translate(glm::mat4(1.0f), transformMatrice);
	for (Object* obj : Camera::objects) {
		obj->setUniformMatrix4fv(Camera::uniform, camera);
	}
}



void Camera::setCameraPosition(GLFWwindow* window){
	glfwSetKeyCallback(window, Camera::key_callback);
	if (right) {
		Camera::transformMatrice.x += Camera::increment;
		Camera::set_uniforms();
	}else if (left) {
		Camera::transformMatrice.x -= Camera::increment;
		Camera::set_uniforms();
	}else if (up) {
		Camera::transformMatrice.y += Camera::increment;
		Camera::set_uniforms();
	}else if (down) {
		Camera::transformMatrice.y -= Camera::increment;
		Camera::set_uniforms();
	}
}
