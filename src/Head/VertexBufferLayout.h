#pragma once

#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

struct VertexBufferElement//顶点缓冲中的元素
{	
	unsigned int type;//类型
	unsigned int count;//数量 
	unsigned char normalized;//标记

	static unsigned int GetSizeOfType(unsigned int type)//获取类型数据长度
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;//步幅
public:
	VertexBufferLayout()
		: m_Stride(0){}

	template <typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template <>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT , count , GL_FALSE });//载入FLOAT类型
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);//步幅增加
	}

	template <>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT , count , GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template <>
	void Push<char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE , count , GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};