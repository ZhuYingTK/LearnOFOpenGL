#pragma once
#include "Test.h"

#include "Head/VertexBuffer.h"
#include "Head/VertexBufferLayout.h"
#include "Head/Texture.h"
#include <memory>

namespace test{

	class TestTexture2D : public Test//材质测试实例
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr <VertexArray> m_VAO;//顶点数组(详见VertexArray.cpp）
		std::unique_ptr <VertexBuffer> m_VB;//顶点缓冲(详见VertexBuffer.cpp）
		std::unique_ptr <IndexBuffer> m_IBO;//索引缓冲(详见IndexBuffer.cpp）
		std::unique_ptr <Shader> m_Shader;//Shader(详见Shader.cpp）
		std::unique_ptr <Texture> m_TextTure;//材质实例(详见TextTure.cpp）

		glm::mat4 m_Proj, m_View;//项目矩阵和视角矩阵

		glm::vec3 m_trainslationA, m_trainslationB;//两个对物体位置的变换向量
	};
}