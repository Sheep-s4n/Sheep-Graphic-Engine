#version 330 core

out vec4 color;
in vec2 texCoords;

uniform vec4 u_color;
uniform vec4 t_color;
uniform vec2 size;
uniform vec2 pos;
uniform bool has_texture;
uniform sampler2D c_texture;

float circle(in vec2 _st, in float _radius) {
	vec2 dist = _st - vec2(0.5);
	return 1. - smoothstep(_radius - (_radius * 0.01),
		_radius + (_radius * 0.01),
		dot(dist, dist) * 4.0);
}

void main() {
	vec2 uv = (gl_FragCoord.xy - vec2(pos.x , pos.y)) / vec2(size.x , size.y);
	vec3 p_color = vec3(circle(uv, 1));
	vec4 texColor = texture(c_texture, texCoords);
	if (p_color.r > 0 || p_color.g > 0 || p_color.b > 0) 
	{
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
	else 
	{
		color.w = 0;
	}

}