#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform sampler2D c_texture;
uniform bool has_texture;
uniform vec4 t_color;
uniform vec4 textColor;
uniform float repeat;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
	vec4 texColor = texture(c_texture, TexCoords * repeat);
	if (has_texture)
	{
		if (texColor.w < 0.1)
			color = textColor * sampled;
		else
			color = texColor * sampled * t_color;
	}
	else
	{
		color = textColor * sampled;
	}
}