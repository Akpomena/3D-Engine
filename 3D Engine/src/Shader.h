#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
public:
	Shader(const char* vertexShader, const char* fragmentShader);
	void Bind();
	
	void SetUniform1i(const char* name, int value);
	void SetUniformMat4(const char* name, glm::mat4 value);
private:
	unsigned int u_ShaderID;

	unsigned int  CompileShader(const char* source, int shaderType);
	void CreateShader(const char* vertexSource, const char* fragmentSource);
};

