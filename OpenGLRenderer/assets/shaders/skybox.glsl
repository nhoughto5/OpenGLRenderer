#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;

out vec3 TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main() {
	vec4 worldPosition = u_Model * vec4(a_Position, 1.0);
	gl_Position = u_Projection * u_View * worldPosition;
	TexCoord = aTexCoord;
}

#type fragment
#version 330 core

out vec4 color;

in vec2 TexCoord;

uniform samplerCube skybox;

void main() {
	color = texture(skybox, TexCoords);
}