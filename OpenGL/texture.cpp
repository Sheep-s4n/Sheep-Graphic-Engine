#include "texture.h"
#include "stb_image.h" // to get image data for texture
#include <iostream>
#include <GLEW/glew.h>


unsigned char* Texture::getTexture(const std::string& path){
    const char* c_str = path.c_str();
    unsigned char* data = stbi_load(c_str, &width, &height , &bitPerPixel , 4); // 4 because 4 channel = R G B A
    return data;
}

bool Texture::exist() {
    return (height != 0 && width != 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture_id);
}

Texture::Texture() : slot(0) , program_id(0) , texture_id(0), width(0), height(0), bitPerPixel(0) {}

void Texture::setTexture(const std::string path , unsigned int program_id , std::string u_name, bool flipImage , int slot) {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Blending = how texture are rendered
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);



    flipImage ? stbi_set_flip_vertically_on_load(1) : stbi_set_flip_vertically_on_load(0); // flip texture to render pixels as OpenGL expect us to 
    unsigned char* textureData = getTexture(path);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D ,texture_id); // !!!
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    glGenerateTextureMipmap(texture_id); // !!!
    //glGenerateMipmap(GL_TEXTURE_2D); 
    int uniformLocation = glGetUniformLocation(program_id, u_name.c_str()); // integer uniform = texture slot 
    glProgramUniform1i(program_id, uniformLocation, slot); // tell shader to get texture from ${slot}

    if (textureData) {
        stbi_image_free(textureData);
        textures.insert(std::make_pair(path, Texture_container(path, slot , texture_id)));
    }
    else
        std::cout << "no data in texture buffer !!!!";

}

void Texture::setTextTexture(unsigned char* texture_data, int width , int height , int slot) {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);


    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, texture_data);
  //  glGenerateTextureMipmap(texture_id);
    //int uniformLocation = glGetUniformLocation(program_id, u_name.c_str()); // integer uniform = texture slot 
    //glProgramUniform1i(program_id, uniformLocation, slot); // tell shader to get texture from ${slot}


    this->slot = slot;
}

void Texture::bind(){
   glActiveTexture(GL_TEXTURE0 + slot);
   glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}


