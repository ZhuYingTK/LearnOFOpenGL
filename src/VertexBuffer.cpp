#include "Head/VertexBuffer.h"
#include "Head/Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)//��ʼ��
{
    GLCall(glGenBuffers(1, &m_RendererID));//���ɶ��㻺��
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));//����ID��
    GLCall(glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW));//��������
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));//����
};

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));//��
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}