#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;

out vec3 TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main() {
	TexCoord = a_Position;
    gl_Position = u_Projection * u_View * (u_Model * vec4(a_Position, 1.0));
}

#type fragment
#version 330 core

out vec4 color;

in vec3 TexCoord;

uniform vec4 uAmbientLight;

uniform samplerCube skybox;

void main() {
	color = vec4((uAmbientLight.rgb * texture(skybox, TexCoord).rgb), 1.0);
}