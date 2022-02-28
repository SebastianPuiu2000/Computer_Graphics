#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;


void main()
{

    vec3 color;

    float Ke = 0.82;

    float light = Ke;

    color = object_color * light;


    out_color = vec4(color, 0.5);
}
