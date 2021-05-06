#include "Test3DObj.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "BufferLayout.h"
#include "VertexArray.h"

#include "Texture.h"
namespace test {

	Test3DObj::Test3DObj()
	{
		float h2Size = 256.0f / 2.f;
		float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0,
		};

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));
		GLCall(glfwSwapInterval(1));

		m_VBO = std::make_unique<VertexBuffer>(vertices, 4 * 4 * sizeof(float));
		m_IBO = std::make_unique<IndexBuffer>(indices, 6);

		m_Proj = glm::ortho(0.f, 1280.f, 0.f, 720.f, -1.0f, 1.0f);
		m_View = glm::translate(glm::mat4(1), glm::vec3(-0, 0, 0));

		m_BufferLayout = new BufferLayout();
		m_BufferLayout->push<float>(2);
		m_BufferLayout->push<float>(2);

		m_VAO = std::make_unique<VertexArray>();

		m_VAO->AddBuffer(*m_VBO, *m_BufferLayout, *m_IBO);

		m_Shader = new Shader("../../res/shader/base.shader");
		m_Shader->Bind();
		m_Texture = new Texture("../../res/png/Res_123.png");
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);
		m_Postion = { 0,0,0 };

		m_Renderer = new Renderer();
	}

	Test3DObj::~Test3DObj() {

	}

	void Test3DObj::OnUpdate(float deltaTime)
	{

	}
	void Test3DObj::OnRender()
	{
		m_Shader->Bind();
		glm::mat4 model = glm::translate(glm::mat4(1), m_Postion);
		m_Shader->SetUniformMat4f("u_MVP", m_Proj * m_View * model);
		m_Renderer->Draw(*m_VAO, *m_IBO, *m_Shader);
	}

	void Test3DObj::OnImGUIRender()
	{
		ImGui::SliderFloat3("position", &m_Postion.x, 0, 960);
	}
}