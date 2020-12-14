#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 outNormal;
out vec2 TexCoord;

uniform mat4 uTransform;

void main() {
	gl_Position = uTransform * vec4(a_Position, 1.0);
	outNormal = aNormal;
	TexCoord = aTexCoord;
}

#type fragment
#version 330 core

out vec4 color;

in vec3 outNormal;
in vec2 TexCoord;

uniform sampler2D texture;

void main() {
	color = texture(texture, TexCoord);
}