#version 460
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_texture_points;

out vec2 f_texture_points;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main() {
   f_texture_points = v_texture_points;
   gl_Position = projection * view * model * vec4(v_position, 1.0);
}