#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTex;

out vec2 fragTex;

uniform mat4 rotMatrix;
uniform mat4 transform;

void main()
{
	gl_Position = transform * rotMatrix * vec4(aPos.x, aPos.y, 0.0, 1.0);
	fragTex = vec2(aTex.x, 1.0 - aTex.y);
}