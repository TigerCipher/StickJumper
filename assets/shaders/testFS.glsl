#version 330 core

in vec2 fragTex;

out vec4 fragColor;


//uniform float sinTime;
//uniform float cosTime;

uniform sampler2D tex;
//uniform sampler2D overlay;
//uniform sampler2D smileTex;
uniform vec4 colorOverlay;

void main()
{
	//vec4 texColor = mix(texture(tex, fragTex), texture(overlay, fragTex), 0.2);
	vec4 texColor = texture(tex, fragTex);
	
	vec4 col = colorOverlay;
	if(col == vec4(0))
	{
		col = vec4(1, 1, 1, 1);
	}
	fragColor = texColor * col;
}