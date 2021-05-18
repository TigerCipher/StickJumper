#version 330 core

in vec4 vColor;
in vec2 fragTex;

out vec4 fragColor;


//uniform float sinTime;
//uniform float cosTime;

uniform sampler2D tex;
//uniform sampler2D smileTex;

void main()
{
	//vec4 texColor = mix(texture(tex, fragTex), texture(smileTex, fragTex), 0.4);
	vec4 texColor = texture(tex, fragTex);
	fragColor = texColor * vColor;
}