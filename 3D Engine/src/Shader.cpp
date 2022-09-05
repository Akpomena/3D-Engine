#include "Shader.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include "glad/glad.h"

Shader::Shader(const char* vertexShader, const char* fragmentShader) :
	m_ShaderID(0)
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
	glUseProgram(m_ShaderID);
}

void Shader::SetUniformInt(std::string name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
} 

void Shader::SetUniformFloat(std::string name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4(std::string name, glm::mat4 value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(value));
}

void Shader::SetUniformVec3(std::string name, glm::vec3 value)
{
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetUniformVec4(std::string name, glm::vec4 value)
{
	glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

int Shader::GetUniformLocation(std::string name)
{
	if (m_UniformLocations.find(name) != m_UniformLocations.end())
		return m_UniformLocations[name];

	int location = glGetUniformLocation(m_ShaderID, name.c_str());

	if (location == -1)
		std::cout << "Invalid Location for: " << name << std::endl;

	m_UniformLocations[name] = location;

	return location;
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
	m_ShaderID = glCreateProgram();
	
	unsigned int vertexShader = CompileShader(vertexSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

	glAttachShader(m_ShaderID, vertexShader);
	glAttachShader(m_ShaderID, fragmentShader);
	glLinkProgram(m_ShaderID);

	int success;
	char infoLog[520];

	glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(m_ShaderID, 520, nullptr, infoLog);

		std::cout << "PROGRAM LINKING FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
