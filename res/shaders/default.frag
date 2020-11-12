#version 460
in  vec2 f_texture_points;
out vec4 f_color;

uniform sampler2D Texture;

void main() {
   f_color = texture(Texture, f_texture_points);
}