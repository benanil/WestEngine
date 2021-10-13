#version 440 core

out vec4 out_color;

in vec2 pos;
in vec2 uv;

uniform sampler2D texture0;

void main() {
	out_color = texture(texture0, uv);
}