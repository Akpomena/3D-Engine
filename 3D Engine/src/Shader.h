#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <unordered_map>

class Shader
{
public:
	Shader(const char* vertexShader, const char* fragmentShader);
	void Bind();
	
	void SetUniformInt(const char* name, int value);
	void SetUniformFloat(const char* name, float value);
	void SetUniformMat4(const char* name, glm::mat4 value);
	void SetUniformVec3(const char* name, glm::vec3 value);
private:
	unsigned int m_ShaderID;
	std::unordered_map<const char*, int> m_UniformLocations;
private:
	int GetUniformLocation(const char* name);
	unsigned int  CompileShader(const char* source, int shaderType);
	void CreateShader(const char* vertexSource, const char* fragmentSource);
};

