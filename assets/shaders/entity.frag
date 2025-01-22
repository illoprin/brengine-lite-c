#version 430

in vec2 out_uv;
in vec3 out_normal;
in vec3 out_fragcoord_ws; // Fragment position in world space

uniform sampler2D u_texture;
uniform vec4 u_color;
uniform bool u_use_texture;

// Camera
uniform vec3 u_cam_pos;

// Lighting
const float u_gamma = 2.2;
const float inv_gamma = 1.0 / u_gamma;
const vec3 u_ambient_light = vec3(0.96, 0.97, 1.0);

// Transperency mask
const vec3 t_mask = vec3(0.91, 0.11, 0.74);

vec4 color_mask(vec4 color)
{
	vec3 d = abs(color.rgb - t_mask);
	if (length(d) < .02) color.a = 0.0;
	return color;
}

out vec4 frag_color;
void main()
{
	vec4 diffuse_color = vec4(1.0);
	if (u_use_texture)
	{
		diffuse_color = texture(u_texture, out_uv);
		diffuse_color = color_mask(diffuse_color);
		if (diffuse_color.a < 0.05) discard;
	}

	diffuse_color *= u_color;

	// Insert to changing color gamma mode
	diffuse_color.rgb = pow(diffuse_color.rgb, vec3(u_gamma));

	// Lighting
	float factor = dot(
		normalize(u_cam_pos - out_fragcoord_ws), 
		out_normal
	) * .5;
	vec3 lighting = u_ambient_light * (.5 + factor);

	// Apply lighting
	diffuse_color.rgb *= lighting;

	// Return to default gamma space
	diffuse_color.rgb = pow(diffuse_color.rgb, vec3(inv_gamma));

	frag_color = diffuse_color;
}