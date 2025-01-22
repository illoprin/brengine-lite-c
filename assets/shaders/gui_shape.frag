#version 430

in vec2 out_uv;

uniform bool u_use_texture;
uniform vec4 u_color;

uniform sampler2D u_texture;

// Transperency mask
const vec3 t_mask = vec3(0.91, 0.11, 0.74);

vec4 color_mask(vec4 color)
{
	vec3 d = abs(color.rgb - t_mask);
	if (length(d) < .01) color.a = 0.0;
	return color;
}

out vec4 frag_color;
void main()
{
	if (u_use_texture)
	{
		vec4 diffuse_color = texture(u_texture, out_uv);
		
		diffuse_color = color_mask(diffuse_color);
		
		if(diffuse_color.a < 0.05)
			discard;
		
		diffuse_color *= u_color;
		
		frag_color = diffuse_color;
	}
	else
	{
		frag_color = u_color;
	}
}