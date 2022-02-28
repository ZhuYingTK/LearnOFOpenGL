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
    //���췽��
	TestTexture2D::TestTexture2D()
        :m_trainslationA(200, 200, 0),m_trainslationB(400, 200, 0),//��ʼ���任����
        m_Proj(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)),//��ʼ����Ŀ����
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))//��ʼ���ӽǾ���
	{
        //��������
        float positions[] = {
         -50.0f, -50.0f, 0.0f, 0.0f,  // 0
          50.0f, -50.0f, 1.0f, 0.0f,  // 1
          50.0f,  50.0f, 1.0f, 1.0f,  // 2
         -50.0f,  50.0f, 0.0f, 1.0f   // 3
        };
        //��������
        unsigned int indices[] = {
            0,1,2,
            0,2,3
        };

        GLCall(glEnable(GL_BLEND));//���û��
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));//���û�ϵķ�ʽ

        m_VAO = std::make_unique<VertexArray>();//������������
        m_VB = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));//�������㻺��
        VertexBufferLayout layout;//�������㻺�岼��
        layout.Push<float>(2);//��ʾǰ����floatΪһ�飨���꣩
        layout.Push<float>(2);//��ʾ������floatΪһ�飨��������)
        m_VAO->AddBuffer(*m_VB, layout);//�ڶ������������뻺��Ͳ���

        m_IBO = std::make_unique<IndexBuffer>(indices, 6);//�������������������ݺ����ݸ���

        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");//����shader
        m_Shader->Bind();//��shader
        m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);//����shader��u_Color�����ݣ�Ŀǰ����ʾ)
        m_TextTure=std::make_unique<Texture>("res/textures/image_Alpha.png");//���ɲ���
        m_Shader->SetUniform1i("u_Texture", 0);
	}
	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}
	void TestTexture2D::OnRender()//������Ⱦ
	{
        //���ֺ���
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;//������Ⱦ��

        m_TextTure->Bind();//�󶨲���

        //��������A
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_trainslationA);//ģ�;���
            glm::mat4 mvp = m_Proj * m_View * model;//ͶӰ����
            m_Shader->Bind();//��shader
            m_Shader->SetUniforMath4f("u_MVP", mvp);//��shader������mvp
            renderer.Draw(*m_VAO, *m_IBO,*m_Shader);//��Ⱦ
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
        ImGui::SliderFloat3("Trainslaton A", &m_trainslationA.x, 0.0f, 960.0f);//���ɿ��Ե���������GUI
        ImGui::SliderFloat3("Trainslaton B", &m_trainslationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}