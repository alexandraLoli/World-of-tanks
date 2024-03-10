#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_color;
in vec3 frag_hp;
in vec3 frag_normal;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Write pixel out color
    out_color = vec4(frag_color - frag_color * (3 - frag_hp.x) / 3, 0);

}
