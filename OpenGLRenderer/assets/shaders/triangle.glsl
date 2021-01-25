#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 aInstanceModelMatrix;

out vec3 outNormal;
out vec2 TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main() {
	vec4 worldPosition = aInstanceModelMatrix * vec4(a_Position,1.0);
	gl_Position = u_Projection * u_View * worldPosition;
	outNormal = aNormal;
	TexCoord = aTexCoord;
}

#type fragment
#version 330 core

out vec4 color;

in vec3 outNormal;
in vec2 TexCoord;

uniform sampler2D t_Ambient;
uniform sampler2D t_Diffuse;

void main() {
	if (TexCoord.x > 0.50)
	{
		color = texture(t_Diffuse, TexCoord);
	}
	else
	{
		color = texture(t_Ambient, TexCoord);
	}
}