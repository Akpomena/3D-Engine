#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    Normal = mat3(transpose(inverse(u_Model))) * aNormal;
    Position = vec3(u_Model * vec4(aPos, 1.0));
    gl_Position = u_Projection * u_View * vec4(Position, 1.0);
}  