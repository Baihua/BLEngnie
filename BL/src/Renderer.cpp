#include "Renderer.h"


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error](" << error << "): " << function << " in file: " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}
void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader)
{
	shader.Bind();
	vao.Bind();
	ibo.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}
void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}