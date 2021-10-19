#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;

out vsOut
{
	vec2 vUV;
	vec3 vNormal;
	vec3 vPosition;
	vec3 vTangent;
	vec3 vBinormal;	
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
	vUV = texCoords;
	vNormal = normal;
	vPosition = vec3(model * vec4(position, 1.0));
	vTangent = tangent;
	vBinormal = cross(tangent, normal);
	gl_Position = projection * view * model * vec4(position, 1);
}