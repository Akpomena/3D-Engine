
#version 400 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoord;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Perspective;

void main()
{
	normal = mat3(transpose(inverse(u_Model))) * a_normal;
	fragPos = vec3(u_Model * vec4(a_Position, 1.0f));

	texCoord = a_texCoord;

	gl_Position = (u_Perspective * u_View * u_Model) * vec4(a_Position, 1.0f);
}

