#version 330 core

in vec4 pos;
layout(location = 1) in vec2 textureCoords;
out vec2 texCoords;

uniform mat4 mvp;
uniform vec2 mouse;

void main() {
    vec4 pos_copy = pos;
    pos_copy.x = pos_copy.x + mouse.x;
    pos_copy.y = pos_copy.y + mouse.y;
    gl_Position = mvp * pos_copy;
    texCoords = textureCoords;
}