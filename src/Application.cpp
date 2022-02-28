/*
����ĿΪ��chernoOpenGL��ѧϰ�ʼ�
�������˶Դ������⣬����֤��ȫ��ȷ
������26P���˺����Ƶ�����뱾��Ŀ��һ�����𣬹ʲ��ڴ��޸�
��test����ǰ�ĺ����������TestTexture2D.cpp
*/


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Head/Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

int main(void)
{
    GLFWwindow* window;

    //���г�ʼ�����ж��Ƿ����glfw
    if (!glfwInit())
        return -1;
    //��ʼ������
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //��������
    window = glfwCreateWindow(1920, 1080, "TRIANGlES", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //��������������
    glfwMakeContextCurrent(window);
    //����glew
    if(glewInit()!=GLEW_OK)
    std::cout << "GLEW_ERROR!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    //������ϣ���png�ļ���͸������Ч��
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    //������Ⱦ��ʵ���������Renderer.cpp��
    Renderer renderer;
    //����imgui�����ģ�imguiΪ���˵Ŀ�
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    //��������ʵ��(�����tests�ļ���)
    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;
    //��test�м���ClearColor��TextTure����������Ŀ
    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestTexture2D>("2D TextTure");

    //ѭ��ֱ���û��رմ���
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();
        //���������Ŀ��������
        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);//����
            currentTest->OnRender();//��ʼ��Ⱦ
            ImGui::Begin("Test");
            if (currentTest != testMenu&&ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();//����Imgui����ؿ��Ƴ���
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        //����ǰ�󻺳�
        glfwSwapBuffers(window);
        glfwSwapInterval(1);

        //ѭ�������¼�
        glfwPollEvents();
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}