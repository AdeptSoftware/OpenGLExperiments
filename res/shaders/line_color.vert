#version 460
layout(location = 0) in vec3 v_position;
out vec3 f_color;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main() {
   f_color = vec3(0.4, 0.4, 0.4);
   gl_Position = projection * view * model * vec4(v_position, 1.0);
}