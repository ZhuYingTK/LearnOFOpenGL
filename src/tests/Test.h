#pragma once

#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace test {
	//Test抽象类
	class Test
	{
	public:
		Test(){}
		virtual ~Test(){}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};
	//测试菜单
	class TestMenu : public	Test
	{
	public:
		TestMenu(Test*& currentTestPointer);//利用多态实现接口

		void OnImGuiRender() override;//重写Imgui

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registerign Test" << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;//包含测试名字和生成测试内容实例的方法
	};
}