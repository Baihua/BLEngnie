#include "TestMenu.h"
#include "Renderer.h"
#include "imgui/imgui.h"
namespace test {
	
	TestMenu::TestMenu(Test*& currentTest):m_CurrrentTest(currentTest)
	{

	}
	
	TestMenu::~TestMenu() {

	}

	void TestMenu::OnUpdate(float deltaTime)
	{

	}
	void TestMenu::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestMenu::OnImGUIRender() 
	{
		for (auto& test : m_Tests)
		{
			if(ImGui::Button(test.first.c_str()))
			{
				m_CurrrentTest = test.second();
			}
		}

	}
}