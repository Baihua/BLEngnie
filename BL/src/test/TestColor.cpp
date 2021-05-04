#include "TestColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"
namespace test {
	
	TestColor::TestColor()
		:m_ClearColor{0.f,0.f,0.f,0.0f}
	{

	}
	
	TestColor::~TestColor() {

	}

	void TestColor::OnUpdate(float deltaTime)
	{

	}
	void TestColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestColor::OnImGUIRender() 
	{
		ImGui::ColorEdit4("clear color", m_ClearColor);
	}
}