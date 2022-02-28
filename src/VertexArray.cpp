#include "Head/VertexArray.h"
#include "Head/VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));//���ɶ�������
}
VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)//���뻺��
{
	Bind();//��Ŀ��
	vb.Bind();//�󶨶��㻺��
	const auto& elements = layout.GetElements();//��ȡ���㻺�岼��
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++)//���Ԫ����������
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));//�󶨵�Ŀ��
}
void VertexArray::unBind() const
{
	GLCall(glBindVertexArray(0));
}