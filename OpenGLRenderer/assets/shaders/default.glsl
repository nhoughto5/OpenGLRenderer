#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 aInstanceModelMatrix;

out vec3 outNormal;
out vec2 outTexCoord;
out vec3 outPos;  

uniform mat4 u_Projection;
uniform mat4 u_View;
//uniform mat4 u_Model;

void main() {
	vec4 worldPosition = aInstanceModelMatrix * vec4(a_Position,1.0);
	gl_Position = u_Projection * u_View * worldPosition;
	outPos = vec3(aInstanceModelMatrix * vec4(a_Position, 1.0));
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

uniform vec4 u_Specular;
uniform float u_MaterialAlpha;

void main() {
    const float kGamma = 0.4545454;
    const float kInverseGamma = 2.2;

	vec3 norm = normalize(outNormal);
	vec3 lightDir = normalize(u_LightPosition - outPos);  
	vec3 diffuse = u_LightParams.w * u_DiffuseColour * max(dot(norm, lightDir), 0.0) * u_LightParams.xyz;
	vec3 viewFragmentDirection = normalize(outPos);
	vec3 viewNormal = normalize(outNormal);
	vec3 reflectedLightDirection = reflect(-lightDir, viewNormal);
	float specularStrength = max(0.0, dot(viewFragmentDirection, reflectedLightDirection));
	vec3 specular = u_LightParams.w * u_Specular.rgb * pow(u_LightParams.w, u_Specular.w);

	vec4 objectColor;
	if (u_DiffuseTextureValid) {
        objectColor = texture(u_DiffuseTexture, outTexCoord);
    } else {
        objectColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    objectColor.rgb = pow(objectColor.rgb, vec3(kInverseGamma));

	color.a = objectColor.a * u_MaterialAlpha;
	vec3 ambient = uAmbientLight.a * uAmbientLight.rgb;
    if (u_DiffuseTextureValid) {
        color.rgb = pow(objectColor.rgb + ambient + diffuse + specular, vec3(kGamma));
    } else {
        color.rgb = pow(objectColor.rgb * (ambient + diffuse) + specular, vec3(kGamma));
    }
}