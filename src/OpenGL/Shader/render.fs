#version 400 core


uniform sampler2D depth_map;
uniform vec3 light_position;
uniform vec3 light_rgb;

in vec3 fs_object_color;
in vec3 fs_object_normal;
in float fs_light_distance;
in vec3 fs_light_dir;
in vec4 fs_object_vertex_light_space;


float ShadowMap(vec4 vertex_light_space)
{
    vec4 light_normal_volume = vertex_light_space.xyzw / vertex_light_space.w;
    light_normal_volume = (light_normal_volume + 1.0) * 0.5;
    
    float shadow_depth = light_normal_volume.z;
    float light_depth = texture(depth_map, light_normal_volume.xy).r;
    
    float bias = 0.0001;
    float shadow = 0.0;
    if (light_depth - shadow_depth > bias)
        shadow = 1.0;
    else
        shadow = 0.2;
    
    return shadow;
}

void main()
{
    float shadow = ShadowMap(fs_object_vertex_light_space);
    float costheta = max(dot(fs_light_dir, fs_object_normal), 0.0f);
    float attenuation = 1.0 / fs_light_distance;
    vec3 diffuse = light_rgb * fs_object_color * attenuation * costheta * shadow;
    vec3 ambient = light_rgb * fs_object_color * attenuation * 0.1;
    vec3 L = ambient + diffuse;

    gl_FragColor = vec4(L, 1.0);
    //gl_FragColor = vec4(fs_object_color, 1.0);

	return;
}