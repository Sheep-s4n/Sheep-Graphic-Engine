#pragma once
#include <string>
#include <unordered_map>

struct Texture_container {
	std::string path;
	int slot;
	unsigned int texture_id;
};

class Texture {
private:
	unsigned int program_id;
	unsigned char* getTexture(const std::string& path);
public:
	int slot;
	int width;
	int height;
	int bitPerPixel;
	~Texture();
	Texture();
	bool exist();
	unsigned int texture_id;
	void setTexture(const std::string path, unsigned int program_id, std::string u_name, bool flipImage, int slot = 0);
	void setTextTexture(unsigned char* texture_data, int width, int height, unsigned int program_id, std::string u_name, int slot=0);
	std::unordered_map<std::string , Texture_container> textures;
	void bind();
	void unbind();
};
