#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 outNormal;
out vec2 outTexCoord;
out vec3 outPos;  

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main() {
	vec4 worldPosition = u_Model * vec4(a_Position,1.0);
	gl_Position = u_Projection * u_View * worldPosition;
	outPos = vec3(u_Model * vec4(a_Position, 1.0));
	outNormal = aNormal;
	outTexCoord = aTexCoord;
}

#type fragment
#version 330 core

out vec4 color;

in vec3 outNormal;
in vec2 outTexCoord;
in vec3 outPos; 

uniform bool u_DiffuseTextureValid;
uniform sampler2D u_DiffuseTexture;
uniform vec3 u_DiffuseColour;

uniform vec3 u_LightPosition;
uniform vec4 u_LightParams;

uniform vec4 uAmbientLight;

uniform bool u_AmbientTextureValid;
uniform sampler2D u_AmbientTexture;

void main() {
	vec3 norm = normalize(outNormal);
	vec3 lightDir = normalize(u_LightPosition - outPos);  
	vec3 diffuse = u_LightParams.w * u_DiffuseColour * max(dot(norm, lightDir), 0.0) * u_LightParams.xyz;
	color = vec4((uAmbientLight.w * uAmbientLight.xyz) + diffuse, 1.0) * (texture(u_DiffuseTexture, outTexCoord));
}