
#version 400 core
layout(location = 0) in vec3 a_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Perspective;

void main()
{
	gl_Position = (u_Perspective * u_View * u_Model) * vec4(a_Position, 1.0f);
}

