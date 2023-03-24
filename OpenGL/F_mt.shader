#version 330 core

out vec4 color;
in vec4 rgb_color;


void main() {
	color = rgb_color;
}