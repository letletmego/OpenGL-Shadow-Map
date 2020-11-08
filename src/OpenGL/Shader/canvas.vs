#version 400

in vec3 vs_canvas_vertex;
in vec2 vs_canvas_st;

out vec2 fs_canvas_st;

void main()
{
	fs_canvas_st = vs_canvas_st;

	gl_Position = vec4(vs_canvas_vertex, 1.0);
}