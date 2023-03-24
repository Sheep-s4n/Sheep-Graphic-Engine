#version 330 core

/*layout(location = 0)*/ in vec4 pos;

vec4 pos_copy = pos;
uniform float add;
out float speed;

void main() {
    speed = add;
    if (pos_copy.x != -1.0f)
        pos_copy.x += add;
    gl_Position = pos_copy;
}