#pragma once
#include <string>


class Shader {
private:
	unsigned int shader_id;
	unsigned int program_id;
	std::string getShader(const std::string& path);
public:
	~Shader();
	Shader(const std::string path, const unsigned int shaderType);
	Shader(const std::string path, const unsigned int shaderType, unsigned int program_id);
	void bindProgram();
	void unbindProgram();
	unsigned int getProgram();
};
