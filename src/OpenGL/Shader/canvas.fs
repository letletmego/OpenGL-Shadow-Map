#version 400

uniform sampler2D depth_map;

in vec2 fs_canvas_st;

void main()
{
	float depth = texture(depth_map, fs_canvas_st).r;

	gl_FragColor = vec4(vec3(depth), 1.0);
}