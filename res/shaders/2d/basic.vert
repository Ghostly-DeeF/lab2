#version 330 core
layout(location = 0) in vec3 vert_pos;
//layout(location = 1) in vec4 vert_color;

uniform vec3 move;
uniform vec4 color;

out vec4 f_color;

void main()
{
    gl_Position = vec4(vert_pos+move, 1.0f);
    f_color = color;
};
