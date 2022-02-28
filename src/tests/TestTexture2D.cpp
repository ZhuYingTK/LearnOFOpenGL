#include "TestTexture2D.h"

#include "Head/Renderer.h"
#include "imgui/imgui.h"

#include "Head/VertexBuffer.h"
#include "Head/VertexBufferLayout.h"
#include "Head/Texture.h"
#include <memory>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {
    //构造方法
	TestTexture2D::TestTexture2D()
        :m_trainslationA(200, 200, 0),m_trainslationB(400, 200, 0),//初始化变换向量
        m_Proj(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)),//初始化项目矩阵
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))//初始化视角矩阵
	{
        //顶点数组
        float positions[] = {
         -50.0f, -50.0f, 0.0f, 0.0f,  // 0
          50.0f, -50.0f, 1.0f, 0.0f,  // 1
          50.0f,  50.0f, 1.0f, 1.0f,  // 2
         -50.0f,  50.0f, 0.0f, 1.0f   // 3
        };
        //索引数组
        unsigned int indices[] = {
            0,1,2,
            0,2,3
        };

        GLCall(glEnable(GL_BLEND));//启用混合
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));//启用混合的方式

        m_VAO = std::make_unique<VertexArray>();//创建顶点数组
        m_VB = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));//创建顶点缓冲
        VertexBufferLayout layout;//创建顶点缓冲布局
        layout.Push<float>(2);//表示前两个float为一组（坐标）
        layout.Push<float>(2);//表示后两个float为一组（纹理坐标)
        m_VAO->AddBuffer(*m_VB, layout);//在顶点数组中载入缓冲和布局

        m_IBO = std::make_unique<IndexBuffer>(indices, 6);//在索引缓冲中载入数据和数据个数

        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");//生成shader
        m_Shader->Bind();//绑定shader
        m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);//导入shader中u_Color的数据（目前不显示)
        m_TextTure=std::make_unique<Texture>("res/textures/image_Alpha.png");//生成材质
        m_Shader->SetUniform1i("u_Texture", 0);
	}
	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}
	void TestTexture2D::OnRender()//启用渲染
	{
        //开局黑屏
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;//生成渲染器

        m_TextTure->Bind();//绑定材质

        //生成物体A
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_trainslationA);//模型矩阵
            glm::mat4 mvp = m_Proj * m_View * model;//投影矩阵
            m_Shader->Bind();//绑定shader
            m_Shader->SetUniforMath4f("u_MVP", mvp);//在shader中载入mvp
            renderer.Draw(*m_VAO, *m_IBO,*m_Shader);//渲染
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_trainslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniforMath4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        }
	}
	void TestTexture2D::OnImGuiRender()
	{
        ImGui::SliderFloat3("Trainslaton A", &m_trainslationA.x, 0.0f, 960.0f);//生成可以调节向量的GUI
        ImGui::SliderFloat3("Trainslaton B", &m_trainslationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}