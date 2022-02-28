#include "Head/IndexBuffer.h"

#include "Head/Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_Count(count)
{
    GLCall(glGenBuffers(1, &m_RendererID));//生成索引缓冲
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));//绑定
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(GLuint), data, GL_STATIC_DRAW));//输入数据
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
};

void  IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void  IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}