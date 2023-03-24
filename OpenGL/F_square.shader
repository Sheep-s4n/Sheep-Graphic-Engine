#version 330 core

out vec4 color;
in vec2 texCoords;

uniform vec4 u_color;
uniform vec4 t_color;
uniform bool has_texture;
uniform sampler2D c_texture;

void main() {
	vec4 texColor = texture(c_texture, texCoords);
	if (has_texture)
	{
		if (texColor.w < 0.1)
			color = u_color;
		else
			color = texColor * t_color;
	}
	else 
	{
		color = u_color;
	}
}