#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTex;

out vec2 fragTex;

//uniform mat4 rotMatrix;
uniform mat4 transform;
uniform mat4 proj;

void main()
{
	//gl_Position = proj * view * transform * vec4(aPos.x, aPos.y, 0.0, 1.0);
	//gl_Position = proj * vec4(aPos.x, aPos.y, 0.0, 1.0);
	gl_Position.xy = (proj * transform * vec4(aPos.x, aPos.y, 0, 1)).xy;
	gl_Position.z = 0;
	gl_Position.w = 1;
	fragTex = vec2(aTex.x, 1.0 - aTex.y);
}