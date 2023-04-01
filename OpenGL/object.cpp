#include "object.h"
#include <GLEW/glew.h>
#include "abstraction.h"
#include <iostream>
#include "settings.h"
#define Size(x , type) (sizeof(x) / sizeof(type))

Object::~Object(){
    glDeleteProgram(program_id);
}

Texture* Object::getTextureI() {
    return &texture;
}

Object::Object() : Z_rotate(0), Transform_from_middle(true), Y_rotate(0), X_rotate(0), proj(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)), R(0), G(0), B(0), A(255), Texture(""), X(0), Y(0) , is_using_dynamic_buffer(false), index_buffer_is_set(false), vertex_buffer_is_set(false) , program_id(glCreateProgram()), point_count(0) {};

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

void Object::draw() {
    if (!point_count) {
        std::cout << "nothing to draw !" << std::endl;
        return;
    }
    bind();
    glDrawElements(GL_TRIANGLES, point_count, GL_UNSIGNED_INT, nullptr);
}

void Object::draw(int mode) {
    if (!point_count) {
        std::cout << "nothing to draw !" << std::endl;
        return;
    }
    bind();
    glDrawElements(mode, point_count, GL_UNSIGNED_INT, nullptr);
}


void Object::drawFromVBO(int coord_count) {
    if (!coord_count) {
        std::cout << "nothing to draw !" << std::endl;
        return;
    }
    bind();
    glDrawArrays(GL_TRIANGLES, 0, coord_count);
}

void Object::drawFromVBO(int coord_count , int mode) {
    if (!coord_count) {
        std::cout << "nothing to draw !" << std::endl;
        return;
    }
    bind();
    glDrawArrays(mode, 0, coord_count);
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



void Object::removeTexture()
{
    Texture = "";
}

void Object::setColors(int c_R, int c_G, int c_B)
{
    R = c_R;
    G = c_G;
    B = c_B;
}

void Object::setColors(int RGB)
{
    R = RGB;
    G = RGB;
    B = RGB;
}

void Object::setColors(int c_R, int c_G, int c_B, int c_A)
{
    R = c_R;
    G = c_G;
    B = c_B;
    A = c_A;
}

void Object::setColorsTexture(int c_R, int c_G, int c_B)
{
    Texture_colors.R = c_R;
    Texture_colors.G = c_G;
    Texture_colors.B = c_B;
}

void Object::setColorsTexture(int RGB)
{
    Texture_colors.R = RGB;
    Texture_colors.G = RGB;
    Texture_colors.B = RGB;
}

void Object::setColorsTexture(int c_R, int c_G, int c_B, int c_A)
{
    Texture_colors.R = c_R;
    Texture_colors.G = c_G;
    Texture_colors.B = c_B;
    Texture_colors.A = c_A;
}

void Object::setPositions(int XY)
{
    X = XY;
    Y = XY;
}

void Object::setPositions(int _X, int _Y)
{
    X = _X;
    Y = _Y;
}

void Object::setPositions(int _X, int _Y, int _Z)
{
    X = _X;
    Y = _Y;
    Z_index = _Z;
}

void Object::setRotation(int Z)
{
    Z_rotate = Z;
}

void Object::setRotations(int X, int Y, int Z)
{
    X_rotate = X;
    Y_rotate = Y;
    Z_rotate = Z;
}

void Object::updateTextureColors() {
    setUniform4f("t_color", (float)Texture_colors.R / 255, (float)Texture_colors.G / 255, (float)Texture_colors.B / 255, (float)Texture_colors.A / 255);
    prev_texture_colors[0] = Texture_colors.R;
    prev_texture_colors[1] = Texture_colors.G;
    prev_texture_colors[2] = Texture_colors.B;
    prev_texture_colors[3] = Texture_colors.A;
}




bool Object::colorChanged()
{
    if (
        R != prev_colors[0] || 
        G != prev_colors[1] || 
        B != prev_colors[2] || 
        A != prev_colors[3]
        ) return true;
    return false;
}

bool Object::rotationChanged()
{
    if (
        X_rotate != prev_rotation[0] ||
        Y_rotate != prev_rotation[1] ||
        Z_rotate != prev_rotation[2]
        ) return true;
    return false;
}

bool Object::textureColorsChanged()
{
    if (
        Texture_colors.R != prev_texture_colors[0] ||
        Texture_colors.G != prev_texture_colors[1] ||
        Texture_colors.B != prev_texture_colors[2] ||
        Texture_colors.A != prev_texture_colors[3]
        ) return true;
    return false;
}


void Object::updateTexture()
{
    if (Texture == "")
    {
        setUniform1b("has_texture", false);
    }
    else
    {
        setUniform1b("has_texture", true);
        setTexture(Texture, "c_texture", true);
    }
    prev_Texture = Texture;
}


void Object::updateColors()
{
    setUniform4f("u_color", (float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255);
    prev_colors[0] = R;
    prev_colors[1] = G;
    prev_colors[2] = B;
    prev_colors[3] = A;
}

void Object::updateRotation()
{
    glm::mat4 mvp =
        glm::rotate(glm::mat4(1.0f), glm::radians((float)Z_rotate), glm::vec3(0.0f, 0.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians((float)Y_rotate), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians((float)X_rotate), glm::vec3(1.0f, 0.0f, 0.0f))
        * proj;
    setUniformMatrix4fv("mvp", mvp);

    prev_rotation[0] = X_rotate;
    prev_rotation[1] = Y_rotate;
    prev_rotation[2] = Z_rotate;
}
