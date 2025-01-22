#version 430

in vec2 in_position;
in vec2 in_texcoord;

out vec2 out_uv;

uniform mat4 u_projection = mat4(1.0);
uniform mat4 u_model = mat4(1.0);

void main()
{
	out_uv = in_texcoord;
	gl_Position = u_projection * u_model * vec4(in_position, 0.0, 1.0);
}