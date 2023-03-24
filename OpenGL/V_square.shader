#version 330 core

in vec4 pos;
layout(location = 1) in vec2 textureCoords;

uniform mat4 mvp;
out vec2 texCoords;

void main() {
    gl_Position = mvp * pos;
    texCoords = textureCoords;
}