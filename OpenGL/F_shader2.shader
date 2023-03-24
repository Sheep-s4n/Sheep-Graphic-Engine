#version 330 core

out vec4 color;
in float speed;

void main() {
	color = vec4(0.0f, 0.0f, 0.0f, 1.0f) + speed / 2;
}