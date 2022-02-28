#include "TestClearColor.h"
#include "Head/Renderer.h"
#include "imgui/imgui.h"

namespace test {

	TestClearColor::TestClearColor()
		: m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f }
	{
	}
	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{

	}
	void TestClearColor::OnRender()//启用渲染
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));//渲染颜色
		GLCall(glClear(GL_COLOR_BUFFER_BIT));//颜色格式
	}
	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);//生成imgui
	}
}