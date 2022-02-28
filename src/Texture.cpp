#include "Head/Texture.h"
#include "Head/stb_image.h"

Texture::Texture(const std::string& path)//根据纹理地址初始化
	:m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);//翻转材质
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);//载入图像缓冲到m_LocalBuffer

	GLCall(glGenTextures(1, &m_RendererID));//生成材质
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));//绑定材质

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));//导入材质
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));//解绑

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);//释放图像
}
Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));//导入材质到渲染槽
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));//绑定材质
}
void Texture::Unbind()
{

}