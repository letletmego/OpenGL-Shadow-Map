#version 400 core


uniform mat4x4 model_transform;
uniform mat4x4 light_transform;
uniform mat4x4 view;
uniform mat4x4 perspective;
uniform mat4x4 light_view;
uniform mat4x4 light_perspective;
uniform vec3 light_position;
uniform vec3 light_rgb;

in vec3 vs_object_vertex;
in vec3 vs_object_color;
in vec3 vs_object_normal;

out vec3 fs_object_color;
out vec3 fs_object_normal;
out float fs_light_distance;
out vec3 fs_light_dir;
out vec4 fs_object_vertex_light_space;


void main()
{
	fs_object_color = vs_object_color;

	fs_object_normal = vs_object_normal;

	vec3 light_transform_p = (light_transform * vec4(light_position, 1.0f)).xyz;
	fs_light_distance = length(light_transform_p - vs_object_vertex);
	fs_light_dir = normalize(light_transform_p - vs_object_vertex);

	fs_object_vertex_light_space =
		light_perspective * light_view * model_transform * vec4(vs_object_vertex, 1.0);

	//vec4 light_normal_volume = fs_object_vertex_light_space.xyzw / fs_object_vertex_light_space.w;
	//light_normal_volume = (light_normal_volume + 1.0) * 0.5;
	//gl_Position = light_normal_volume;

	gl_Position = perspective * view * vec4(vs_object_vertex, 1.0);

	return;
}