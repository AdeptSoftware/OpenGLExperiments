#version 460
in vec2 texture_pts;
out vec4 frag_color;

uniform sampler2D Texture;

void main() {
   frag_color = texture(Texture, texture_pts);
}