#include "Head/VertexBuffer.h"
#include "Head/Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)//初始化
{
    GLCall(glGenBuffers(1, &m_RendererID));//生成顶点缓冲
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));//根据ID绑定
    GLCall(glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW));//载入数据
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));//析构
};

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));//绑定
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}