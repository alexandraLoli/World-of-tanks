#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_tex_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform vec3 health_points;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_color;
out vec3 frag_hp;
out vec3 frag_normal;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_color = object_color;
    frag_normal = v_normal * 0.5;
    float hp;
    if (health_points.x < 0) {
        frag_hp = vec3(0, 0, 0);
        hp = 0;
    }
    else {
        frag_hp = health_points;
        hp = health_points.x;
    }

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(v_position + v_normal * (3 - hp) / 3, 1.0);

}
