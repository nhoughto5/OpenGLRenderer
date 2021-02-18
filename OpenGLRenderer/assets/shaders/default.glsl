#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in mat4 aInstanceModelMatrix;

out vec3 outNormal;
out vec2 outTexCoord;
out vec3 outPos;
out vec3 cameraPos;
out vec4 fragPosLightSpace;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_LightSpaceMatrix;

void main() {
    vec4 worldPosition = aInstanceModelMatrix * vec4(a_Position, 1.0);
    gl_Position = u_Projection * u_View * worldPosition;
    outPos = vec3(aInstanceModelMatrix * vec4(a_Position, 1.0));
    outNormal = transpose(inverse(mat3(aInstanceModelMatrix))) * aNormal;
    outTexCoord = aTexCoord;
	cameraPos = vec3(inverse(u_View)[3]);
    fragPosLightSpace = u_LightSpaceMatrix * worldPosition;
}

#type fragment
#version 330 core

out vec4 color;

in vec3 outNormal; in vec2 outTexCoord; in vec3 outPos;
in vec3 cameraPos;
in vec4 fragPosLightSpace;

uniform bool u_DiffuseTextureValid;
uniform sampler2D u_DiffuseTexture;
uniform vec3 u_DiffuseColour;

uniform vec3 u_LightPosition;
uniform vec3 u_LightAttenuation;
uniform vec4 u_LightParams;
uniform vec3 u_SpotDirection;
uniform bool u_isSpotLight;
uniform bool u_isPointLight;
uniform float u_SpotInnerAngle;
uniform float u_SpotOuterAngle;

uniform vec4 uAmbientLight;

uniform bool u_AmbientTextureValid;
uniform sampler2D u_AmbientTexture;

uniform bool u_SpecularTextureValid;
uniform sampler2D u_SpecularTexture;
uniform vec4 u_Specular;

uniform sampler2D u_BumpTexture;
uniform bool u_BumpTextureValid;

uniform float u_MaterialAlpha;

uniform sampler2D shadowMap;

float shadowCalc(vec4 fragLightSpace)
{
    vec3 projCoords = fragLightSpace.xyz / fragLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    return projCoords.z > closestDepth ? 1.0 : 0.0;
}

void main() {
    const float kGamma = 0.4545454;
    const float kInverseGamma = 2.2;

    vec3 norm;
    if (u_BumpTextureValid) {
        norm = normalize(texture(u_BumpTexture, outTexCoord).xyz);
    } else {
        norm = normalize(outNormal);
    }

    vec3 lightDir;
    if (u_isPointLight || u_isSpotLight) {
        lightDir = normalize(u_LightPosition - outPos);
    } else {
        lightDir = normalize(-u_SpotDirection);
    }

    vec3 viewFragmentDirection = normalize(cameraPos - outPos);
    vec3 viewNormal = normalize(outNormal);

    float lightDistance = length(u_LightPosition - outPos);
    float attenuation = 1.0;
    if (u_isPointLight) {
        attenuation = 1.0 / (u_LightAttenuation.x + (lightDistance * u_LightAttenuation.y) + (lightDistance * lightDistance * u_LightAttenuation.z));
    }

    vec3 diffuse = u_LightParams.w * u_DiffuseColour * max(dot(norm, lightDir), 0.0) * u_LightParams.xyz;
    vec3 reflectedLightDirection = reflect(-lightDir, viewNormal);

    vec3 specular;
    if (u_SpecularTextureValid) {
        float spec = pow(max(dot(viewNormal, reflectedLightDirection), 0.0), u_Specular.w);
        specular = u_LightParams.xyz * spec * vec3(texture(u_SpecularTexture, outTexCoord));
    } else {
        float specularStrength = max(0.0, dot(viewFragmentDirection, reflectedLightDirection));
        specular = u_LightParams.w * u_Specular.rgb * pow(u_LightParams.w, u_Specular.w);
    }

    float spotFade = 1.0;
    if (u_isSpotLight && u_isPointLight) {
	    float spotlightTheta = dot(lightDir, normalize(-u_SpotDirection));
        spotFade = (u_SpotInnerAngle - spotlightTheta) / (u_SpotOuterAngle - u_SpotInnerAngle);
        if (spotlightTheta < u_SpotInnerAngle) {
            specular = vec3(0, 0, 0);
            diffuse = vec3(0, 0, 0);
        }
    }

    vec4 objectColor;
    if (u_DiffuseTextureValid) {
        objectColor = texture(u_DiffuseTexture, outTexCoord);
    } else {
        objectColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    objectColor.rgb = pow(objectColor.rgb, vec3(kInverseGamma));

    color.a = objectColor.a * u_MaterialAlpha;
    vec3 ambient = uAmbientLight.a * uAmbientLight.rgb;

    ambient *= attenuation;
    diffuse *= attenuation * spotFade;
    specular *= attenuation * spotFade;

    if (u_DiffuseTextureValid) {
        color.rgb = pow(objectColor.rgb + ambient + ((1.0 - shadowCalc(fragPosLightSpace))*(diffuse + specular)), vec3(kGamma));
    } else {
        color.rgb = pow(objectColor.rgb * (ambient + diffuse) + specular, vec3(kGamma));
    }
}