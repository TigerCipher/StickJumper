#version 330 core

out vec4 fragColor;


uniform float sinTime;
uniform float cosTime;

void main()
{
	fragColor = vec4(1.0, 1.0 * cosTime, 1.0 * sinTime, 1.0);
}