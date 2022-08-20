#include "Shader.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include "glad/glad.h"

Shader::Shader(const char* vertexShader, const char* fragmentShader) :
	u_ShaderID(0)
{
	std::ifstream vertexFile(vertexShader);
	std::ifstream fragmentFile(fragmentShader);

	if (vertexFile.is_open() && fragmentFile.is_open())
	{  
		// Read Vertex Shader
		
		std::stringstream vertexSource;
		vertexSource << vertexFile.rdbuf();
		vertexFile.close();

		// Read Fragment Shader
		std::stringstream fragmentSource;
		fragmentSource << fragmentFile.rdbuf();
		fragmentFile.close();

		// Create Shader

		CreateShader(vertexSource.str().c_str(), fragmentSource.str().c_str());
	}
	else
	{
		std::cout << "FILE COULD NOT OPEN: " << vertexShader << " OR: " << fragmentShader << std::endl;

		vertexFile.close();
		fragmentFile.close();
	}

}

void Shader::Bind()
{
	glUseProgram(u_ShaderID);
}

void Shader::SetUniform1i(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(u_ShaderID, name), value);
}

void Shader::SetUniformMat4(const char* name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(u_ShaderID, name), 1, false, glm::value_ptr(value));
}

unsigned int  Shader::CompileShader(const char* source, int shaderType)
{
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int success;
	char infoLog[520];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 520, nullptr, infoLog);

		std::cout << "SHADER::" << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

void Shader::CreateShader(const char* vertexSource, const char* fragmentSource)
{
	u_ShaderID = glCreateProgram();
	
	unsigned int vertexShader = CompileShader(vertexSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

	glAttachShader(u_ShaderID, vertexShader);
	glAttachShader(u_ShaderID, fragmentShader);
	glLinkProgram(u_ShaderID);

	int success;
	char infoLog[520];

	glGetProgramiv(u_ShaderID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(u_ShaderID, 520, nullptr, infoLog);

		std::cout << "PROGRAM LINKING FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
