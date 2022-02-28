/*
本项目为对chernoOpenGL的学习笔记
仅代表本人对代码的理解，不保证完全正确
更新至26P，此后的视频代码与本项目有一定区别，故不在此修改
在test内容前的函数主体详见TestTexture2D.cpp
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

    //进行初始化，判断是否加载glfw
    if (!glfwInit())
        return -1;
    //初始化窗口
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //创建窗口
    window = glfwCreateWindow(1920, 1080, "TRIANGlES", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //创建窗口上下文
    glfwMakeContextCurrent(window);
    //加载glew
    if(glewInit()!=GLEW_OK)
    std::cout << "GLEW_ERROR!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    //启动混合（对png文件的透明度生效）
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    //创建渲染器实例（详情见Renderer.cpp）
    Renderer renderer;
    //创建imgui上下文，imgui为他人的库
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    //创建测试实体(详情见tests文件夹)
    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;
    //往test中加载ClearColor和TextTure两个测试项目
    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestTexture2D>("2D TextTure");

    //循环直至用户关闭窗口
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();
        //如果测试项目中有内容
        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);//更新
            currentTest->OnRender();//开始渲染
            ImGui::Begin("Test");
            if (currentTest != testMenu&&ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();//生成Imgui的相关控制程序
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        //交换前后缓冲
        glfwSwapBuffers(window);
        glfwSwapInterval(1);

        //循环处理事件
        glfwPollEvents();
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}