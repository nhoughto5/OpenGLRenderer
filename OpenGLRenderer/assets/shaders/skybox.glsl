#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;

out vec3 TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main() {
	TexCoord = a_Position;
    gl_Position = u_Projection * u_View * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

out vec4 color;

in vec3 TexCoord;

uniform samplerCube skybox;

void main() {
	//color = vec4(1.0, 0.0, 1.0, 1.0);
	color = texture(skybox, TexCoord);
}