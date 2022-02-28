#include "Test.h"
#include "imgui/imgui.h"

namespace test {
	TestMenu::TestMenu(Test*& currentTestPointer)
		:m_CurrentTest(currentTestPointer)
	{
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))//创建按钮
				m_CurrentTest = test.second();//启用构造函数
		}
	}
}