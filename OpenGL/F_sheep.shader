#version 330 core

out vec4 color;
in vec2 texCoords;

uniform vec4 u_color;
uniform sampler2D c_texture;

void main() {
	vec4 texColor = texture(c_texture, texCoords) * u_color;
	color = texColor;
}