#pragma once
#include "Test.h"

#include "Head/VertexBuffer.h"
#include "Head/VertexBufferLayout.h"
#include "Head/Texture.h"
#include <memory>

namespace test{

	class TestTexture2D : public Test//���ʲ���ʵ��
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr <VertexArray> m_VAO;//��������(���VertexArray.cpp��
		std::unique_ptr <VertexBuffer> m_VB;//���㻺��(���VertexBuffer.cpp��
		std::unique_ptr <IndexBuffer> m_IBO;//��������(���IndexBuffer.cpp��
		std::unique_ptr <Shader> m_Shader;//Shader(���Shader.cpp��
		std::unique_ptr <Texture> m_TextTure;//����ʵ��(���TextTure.cpp��

		glm::mat4 m_Proj, m_View;//��Ŀ������ӽǾ���

		glm::vec3 m_trainslationA, m_trainslationB;//����������λ�õı任����
	};
}