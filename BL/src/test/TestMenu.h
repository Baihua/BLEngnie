#pragma once
#include "Test.h"
#include <vector>
#include <functional>
#include <string>
namespace test {
	class TestMenu: public  test::Test
	{
	public:
		TestMenu(Test*& currentTest);
		virtual ~TestMenu();

		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();
		virtual void OnImGUIRender();

		template<typename T>
		void Register(const char  * name)
		{
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
	private:
		Test*& m_CurrrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}