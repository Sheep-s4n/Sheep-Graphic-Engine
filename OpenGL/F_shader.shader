#version 330 core

out vec4 color;
in vec2 texCoords;

uniform vec4 i_color;
uniform sampler2D tex;

void main() {
	vec4 texColor = texture(tex, texCoords);
	if (texColor.w >= 0 && texColor.w < 0.9)
		color = i_color;
	else 
		color = texColor;

}