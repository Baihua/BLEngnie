#pragma once
#include "Test.h"

namespace test {
	class TestColor: public test::Test
	{
	public:
		TestColor();
		virtual ~TestColor();

		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();
		virtual void OnImGUIRender();
	private:
		float m_ClearColor[4];
	};
}