#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 outTexCoord;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	outTexCoord = aTexCoord;
}

#type fragment
#version 330 core
out vec4 color;
in vec2 outTexCoord;
uniform sampler2D debugTexture;

void main() {
	//color = vec4(1.0, 1.0, 0.0, 1.0);
	color = texture(debugTexture, outTexCoord);
}