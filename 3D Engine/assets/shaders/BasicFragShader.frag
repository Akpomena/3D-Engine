#version 400 core
layout(location = 0) out vec4 color;

in 	vec2 o_TexCoord;

uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

void main()
{
	color = mix(texture(u_Texture0, o_TexCoord), texture(u_Texture1, o_TexCoord), 0.3);
}