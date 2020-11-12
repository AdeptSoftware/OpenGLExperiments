#version 460
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 texture_points;
out vec2 texture_pts;

void main() {
   texture_pts = texture_points;
   gl_Position = vec4(vertex_position, 1.0);
}