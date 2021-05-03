#include "Shader.h"
#include "Renderer.h"
#include <fstream>
#include <sstream>

Shader::Shader(const char* fileName)
{
	ShaderProgramSource soure =  ParseShaderFromFile(fileName);
	m_RenderID = CreateShader(soure.vertexShader, soure.fragmentShader);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RenderID));
}
void Shader::Bind() const
{
	GLCall(glUseProgram(m_RenderID));
}
void Shader::Unbind() const 
{
	GLCall(glUseProgram(0));
}
void Shader::SetUniform1i(const char* name, int value)
{
	int location = GetUniformLocation(name);
	GLCall(glUniform1i(location, value));
}
void Shader::SetUniformMat4f(const char* name, const glm::mat4& matrix)
{
	int location = GetUniformLocation(name);
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}
void Shader::SetUniform4f(const char* name, float f0, float f1, float f2, float f3)
{
	int location = GetUniformLocation(name);
	GLCall(glUniform4f(location, f0, f1, f2, f3));
}

int Shader::GetUniformLocation(const char* name) {
	GLCall(int location = glGetUniformLocation(m_RenderID, name));
	if (location == -1)
	{
		std::cout << "No this uniform " << name << std::endl;
		ASSERT(false);
	}
	return location;
}

ShaderProgramSource Shader::ParseShaderFromFile(const char* file)
{
	std::ifstream stream(file);
	std::string line;
	std::stringstream ss[2];
	int type = -1;
	while (getline(stream, line))
	{
		if (line.find("#vertex") != std::string::npos)
			type = 0;
		else if (line.find("#fragment") != std::string::npos)
			type = 1;
		else
		{
			if (type != -1)
			{
				ss[type] << line << "\n";
			}
		}
	}
	return{ ss[0].str(),ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to complie " << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}
int Shader::CreateShader(std::string vertexShader, std::string fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	return program;
}