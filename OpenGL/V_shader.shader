#version 330 core

/*layout(location = 0)*/ in vec4 pos;
layout(location = 1) in vec2 textureCoords;

out vec2 texCoords;
uniform mat4 projection;

void main() {

    gl_Position = pos * projection;
    texCoords = textureCoords;
}