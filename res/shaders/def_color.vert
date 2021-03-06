#version 460
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
out vec3 f_color;

void main() {
   f_color = v_color;
   gl_Position = vec4(v_position, 1.0);
}