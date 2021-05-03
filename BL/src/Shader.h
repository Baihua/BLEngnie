#pragma once
#include <string>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader
{
private:
	unsigned int m_RenderID;

public:
	Shader(const char* fileName);
	~Shader();
	void Bind() const;
	void Unbind()const;
	void SetUniform4f(const char* name, float f0, float f1, float f2, float f3);
	void SetUniformMat4f(const char* name, const glm::mat4& matrix);
	void SetUniform1i(const char* name, int value);
private:
	int GetUniformLocation(const char* name);
	ShaderProgramSource ParseShaderFromFile(const char* file);
	int CreateShader(std::string vertexShader, std::string fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
};

