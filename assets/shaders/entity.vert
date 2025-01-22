#version 430

in vec3 in_position;
in vec2 in_texcoord;
in vec3 in_normal;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

out vec2 out_uv;
out vec3 out_normal;
out vec3 out_fragcoord_ws; // Fragment position in world space

void main()
{
	out_normal = mat3(transpose(inverse(u_model))) * in_normal;
	out_fragcoord_ws = (u_model * vec4(in_position, 1.0)).xyz;
	out_uv = in_texcoord;
	gl_Position = u_projection * u_view * u_model * vec4(in_position, 1.0);
}