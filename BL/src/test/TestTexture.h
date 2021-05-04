#pragma once
#include "Test.h"
#include "glm/glm.hpp"
#include <memory>
//#include "VertexBuffer.h"
//#include "IndexBuffer.h"
class VertexBuffer;
class VertexArray;
class IndexBuffer;
class BufferLayout;
class Shader;
class Texture;
class Renderer;
namespace test {
	class TestTexture: public test::Test
	{
	public:
		TestTexture();
		virtual ~TestTexture();

		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();
		virtual void OnImGUIRender();
	private:

		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IBO;

		BufferLayout* m_BufferLayout;
		Shader* m_Shader;
		Texture* m_Texture;
		Renderer* m_Renderer;
		glm::mat4 m_View;
		glm::mat4 m_Proj;
		glm::vec3 m_Postion;

	};
}