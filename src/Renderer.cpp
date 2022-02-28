#include "Head/Renderer.h"

#include <iostream>

//验错函数（调试用）
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error](" << error << "):" << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}



void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const//渲染
{
    shader.Bind();//绑定shader
    va.Bind();//绑定顶点数组
    ib.Bind();//绑定索引缓冲
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));//渲染
}

void Renderer::Clear() const//清除
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}