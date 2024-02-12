#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 center;
layout (location = 2) in vec2 quad_scale;
layout (location = 3) in vec4 Color;
layout (location = 4) in vec4 TexCoords;

uniform mat4 proj_matrix;
uniform vec2 spriteatlas_dim;
uniform vec2 camera_position;
uniform int scale_factor;

out vec4 out_color;
out vec2 out_tex;
out vec4 world_position;

void main()
{
	mat4 translate = mat4(
			 vec4(1.0, 0.0, 0.0, 0.0),
			 vec4(0.0, 1.0, 0.0, 0.0),
			 vec4(0.0, 0.0, 1.0, 0.0),
			 vec4(center, 1.0));
	mat4 cam_translate = mat4(
			 vec4(1.0, 0.0, 0.0, 0.0),
			 vec4(0.0, 1.0, 0.0, 0.0),
			 vec4(0.0, 0.0, 1.0, 0.0),
			 vec4(-camera_position.x, -camera_position.y, 0.0, 1.0));
	mat4 scale = mat4(
			 vec4(quad_scale.x, 0.0, 0.0, 0.0),
			 vec4(0.0, quad_scale.y, 0.0, 0.0),
			 vec4(0.0, 0.0, 1.0, 0.0),
			 vec4(0.0, 0.0, 0.0, 1.0));
	mat4 cam_scale = mat4(
			 vec4(scale_factor, 0.0, 0.0, 0.0),
			 vec4(0.0, scale_factor, 0.0, 0.0),
			 vec4(0.0, 0.0, 1.0, 0.0),
			 vec4(0.0, 0.0, 0.0, 1.0));
	mat4 tex_translate = mat4(
			 vec4(1.0, 0.0, 0.0, 0.0),
			 vec4(0.0, 1.0, 0.0, 0.0),
			 vec4(0.0, 0.0, 1.0, 0.0),
			 vec4(TexCoords.x + (0.5f * TexCoords.z), TexCoords.y + (0.5f * TexCoords.w),  0.0, 1.0));
	mat4 tex_scale = mat4(
			 vec4(TexCoords.z, 0.0, 0.0, 0.0),
			 vec4(0.0, TexCoords.w, 0.0, 0.0),
			 vec4(0.0, 0.0, 1.0, 0.0),
			 vec4(0.0, 0.0, 0.0, 1.0));
	mat4 normal_tex_scale = mat4(
			vec4(1/spriteatlas_dim.x, 0.0, 0.0, 0.0),
			 vec4(0.0, 1/spriteatlas_dim.y, 0.0, 0.0),
			 vec4(0.0, 0.0, 1/spriteatlas_dim.x, 0.0),
			 vec4(0.0, 0.0, 0.0, 1/spriteatlas_dim.y));

	 gl_Position = proj_matrix * cam_translate * cam_scale * translate * scale * vec4(pos, 0.0, 1.0); 
	 out_color = Color;
	 out_tex = (normal_tex_scale * tex_translate * tex_scale * vec4(pos, 0.0, 1.0)).xy;
	 world_position = translate * scale * vec4(pos, 0.0, 1.0);
}
