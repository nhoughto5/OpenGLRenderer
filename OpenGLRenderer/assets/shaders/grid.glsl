#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main() {
	vec4 worldPosition = vec4(a_Position,1.0);
	gl_Position = u_Projection * u_View * worldPosition;
}

#type fragment
#version 330 core

out vec4 color;

void main() {
	color = vec4(0.640f, 0.640f, 0.640f, 1.0f);
}