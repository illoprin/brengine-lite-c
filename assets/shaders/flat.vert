#version 430

in vec2 in_position;
in vec2 in_texcoord;

out vec2 out_uv;

uniform mat4 u_projection;
uniform mat2 u_rotation_mat;
uniform vec2 u_position;
uniform vec2 u_scaliling;

void main()
{
	out_uv = in_texcoord;

	vec2 pos = (u_rotation_mat * (in_position + u_position)) * u_scaliling;
	gl_Position = u_projection * vec4(pos, 0.0, 1.0);
}