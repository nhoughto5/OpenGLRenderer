#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;

uniform mat4 uTransform;

void main() {
	gl_Position = uTransform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

out vec4 color;

void main() {
	color = vec4(0.640f, 0.640f, 0.640f, 1.0f);
}