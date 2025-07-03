#version 330 core
layout(location = 0) in vec3 vert_pos;

uniform mat4 transform;
uniform vec4 color;

out vec4 f_color;

void main()
{
    gl_Position = transform * vec4(vert_pos, 1.0f);
    f_color = color;
};
