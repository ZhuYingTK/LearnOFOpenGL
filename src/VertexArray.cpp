#include "Head/VertexArray.h"
#include "Head/VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));//生成顶点数组
}
VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)//输入缓冲
{
	Bind();//绑定目标
	vb.Bind();//绑定顶点缓冲
	const auto& elements = layout.GetElements();//获取顶点缓冲布局
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++)//逐个元素载入数组
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));//绑定到目标
}
void VertexArray::unBind() const
{
	GLCall(glBindVertexArray(0));
}