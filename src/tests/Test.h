#pragma once

#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace test {
	//Test������
	class Test
	{
	public:
		Test(){}
		virtual ~Test(){}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};
	//���Բ˵�
	class TestMenu : public	Test
	{
	public:
		TestMenu(Test*& currentTestPointer);//���ö�̬ʵ�ֽӿ�

		void OnImGuiRender() override;//��дImgui

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registerign Test" << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;//�����������ֺ����ɲ�������ʵ���ķ���
	};
}