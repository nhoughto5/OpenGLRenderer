#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 outNormal;
out vec2 outTexCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main() {
	vec4 worldPosition = u_Model * vec4(a_Position,1.0);
	gl_Position = u_Projection * u_View * worldPosition;
	outNormal = aNormal;
	outTexCoord = aTexCoord;
}

#type fragment
#version 330 core

out vec4 color;

in vec3 outNormal;
in vec2 outTexCoord;

uniform sampler2D t_Ambient;
uniform sampler2D t_Diffuse;

void main() {
	color = texture(t_Diffuse, outTexCoord);
}