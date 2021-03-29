#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in mat4 aInstanceModelMatrix;

uniform mat4 u_LightSpaceMatrix;

void main()
{
    vec4 t = u_LightSpaceMatrix * aInstanceModelMatrix * vec4(a_Position, 1.0);
    gl_Position = vec4(0.50, 0.50, 0.50, 0.50);
} 

#type fragment
#version 330 core
void main() {

}