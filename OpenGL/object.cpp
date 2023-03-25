#include "object.h"
#include <GLEW/glew.h>
#include "abstraction.h"
#include <iostream>


Object::~Object(){
    glDeleteProgram(program_id);
}

Texture* Object::getTextureI() {
    return &texture;
}

Object::Object() : is_using_dynamic_buffer(false), index_buffer_is_set(false), vertex_buffer_is_set(false) , program_id(glCreateProgram()), point_count(0) {};

int Object::getUniformID(std::string& name) {
    if (uniforms.find(name) == uniforms.end()) {
        uniforms[name] = glGetUniformLocation(program_id, name.c_str());
        return uniforms[name];
    }
    else {
        return uniforms[name];
    }
}

void Object::bind(){
    glUseProgram(program_id);
    if (texture.exist()) {
        texture.bind();
    }
    vertexArray.bind();
}

void Object::setStaticIndexBuffer(unsigned int arr[], int arrSize){
    vertexArray.bind();
    S_indexBuffer.bind();
    point_count = arrSize;
    S_indexBuffer.setData(arr, arrSize, GL_STATIC_DRAW);

    is_using_dynamic_buffer = false;
}

void Object::setDynamicIndexBuffer(unsigned int arr[], int arrSize) {
    vertexArray.bind();
    if (index_buffer_is_set)
    {
        D_indexBuffer.bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, arrSize, arr);
    }
    else
    {
        D_indexBuffer.bind();
        point_count = arrSize;
        D_indexBuffer.setData(arr, arrSize, GL_DYNAMIC_DRAW);
        index_buffer_is_set = true;
        is_using_dynamic_buffer = true;
    }
}

void Object::setStaticVertexBuffer(float arr[], int arrSize){
    vertexArray.bind();

    S_vertexBuffer.bind();
    S_vertexBuffer.setData(arr,arrSize , GL_STATIC_DRAW);

    is_using_dynamic_buffer = false;
}

void Object::setDynamicVertexBuffer(float arr[], int arrSize) { 
    vertexArray.bind();
    if (vertex_buffer_is_set)
    {
        D_vertexBuffer.bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, arrSize, arr);
    }
    else
    {
        D_vertexBuffer.bind();
        D_vertexBuffer.setData(arr, arrSize, GL_DYNAMIC_DRAW);
        vertex_buffer_is_set = true;
        is_using_dynamic_buffer = true;
    }
}

void Object::setVertexBufferLayout(int index, int vertexCount, int stride, int begin) {
    if (is_using_dynamic_buffer) {
        D_vertexBuffer.bind();
        D_vertexBuffer.layout(index, vertexCount, stride, begin);
    }
    else {
        S_vertexBuffer.bind();
        S_vertexBuffer.layout(index , vertexCount , stride , begin);
    }
}

void Object::setShader(const std::string path, const unsigned int shaderType){
    Shader shader(path , shaderType , program_id);
}

void Object::setTexture(const std::string path , std::string name , bool flipImage, int slot){
    texture.slot = slot;
    if(texture.textures.count(path) > 0)
    {
        texture.texture_id = texture.textures[path].texture_id;
        setUniform1i("c_texture", slot);
    }
    else 
    {
        texture.setTexture( path , program_id ,name ,flipImage, slot );
    }
}

int Object::getTextureSlot(const std::string path) 
{
    if (texture.textures.count(path) > 0) return texture.textures[path].slot;
    return texture.textures.size();
}


void Object::unbind(){
    glUseProgram(0);
}

unsigned int Object::getProgram(){
    return program_id;
}


void Object::setUniform1f(std::string name, float value) {
    glProgramUniform1f(
        program_id,
        getUniformID(name),
        value
    );
}

void Object::setUniform1b(std::string name, bool value) {
    glProgramUniform1i(
        program_id,
        getUniformID(name),
        value
    );
}

void Object::setUniform1i(std::string name, int value) {
    glProgramUniform1i(
        program_id,
        getUniformID(name),
        value
    );
}

void Object::setUniform4f(std::string name, float value1 , float value2 , float value3 , float value4) {
    glProgramUniform4f(
        program_id,
        getUniformID(name),
        value1 , value2, value3 , value4
    );
}

void Object::setUniform2f(std::string name, float value1, float value2) {
    glProgramUniform2f(
        program_id,
        getUniformID(name),
        value1, value2
    );
}


void Object::setUniformMatrix4fv(std::string name, glm::mat4& first_value) {
    glProgramUniformMatrix4fv(
        program_id,
        getUniformID(name),
        1, GL_FALSE, 
        &first_value[0][0]
    );

}

void Object::draw() {
    if (!point_count) {
        std::cout << "nothing to draw !" << std::endl;
        return;
    }
    bind();
    glDrawElements(GL_TRIANGLES, point_count, GL_UNSIGNED_INT, nullptr);
}


