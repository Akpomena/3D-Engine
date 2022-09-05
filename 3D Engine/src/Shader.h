#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <unordered_map>

class Shader
{
public:
	Shader(const char* vertexShader, const char* fragmentShader);
	void Bind();
	
	void SetUniformInt(std::string name, int value);
	void SetUniformFloat(std::string name, float value);
	void SetUniformMat4(std::string name, glm::mat4 value);
	void SetUniformVec3(std::string name, glm::vec3 value);
	void SetUniformVec4(std::string name, glm::vec4 value);
private:
	unsigned int m_ShaderID;
	std::unordered_map<std::string, int> m_UniformLocations;
private:
	int GetUniformLocation(std::string name);
	unsigned int  CompileShader(const char* source, int shaderType);
	void CreateShader(const char* vertexSource, const char* fragmentSource);
};

