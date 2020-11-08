#version 400 core

uniform mat4x4 model_transform;
uniform mat4x4 light_view;
uniform mat4x4 light_perspective;

in vec3 vs_object_vertex;

void main()
{
	gl_Position = light_perspective * light_view * model_transform * vec4(vs_object_vertex, 1.0);
}