#include "Head/Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Head/Renderer.h"

Shader::Shader(const std::string& filepath)
    :m_FilePath(filepath), m_RendererID(0)
{
    /* ���ļ��н�����ɫ��Դ�� */
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));//������Ⱦ
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));//����0��ַ������Ⱦ����
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{

    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));//��shader���������
}

void Shader::SetUniforMath4f (const std::string& name,const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);//�ж��Ƿ��ܴ��ļ�
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };//ö��shader����

    std::string line;//shaer�����ÿһ��
    std::stringstream ss[2];//string��(��������shader�Ĵ���)
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) //�ҵ���ɫ��
        {
            if (line.find("vertex") != std::string::npos)//�ҵ�������ɫ��
            {
                type = ShaderType::VERTEX;//����vertex��
            }
            else if (line.find("fragment") != std::string::npos) //�ҵ�ƬԪ��ɫ��
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';//�������
        }
    }
    return { ss[0].str(),ss[1].str() };//����������
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id;
    GLCall(id = glCreateShader(type));//������Ӧ��shader
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));//����Դ��
    GLCall(glCompileShader(id));//����shader

    //������
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); // ��ȡ��ǰ��ɫ������״̬
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length)); // ��ȡ��־����
        char* msg = (char*)alloca(length * sizeof(char)); //������־����
        GLCall(glGetShaderInfoLog(id, length, &length, msg)); // ��ȡ��־��Ϣ
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << msg << std::endl;
        GLCall(glDeleteShader(id)); // ɾ����ɫ��
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program;//�����ʶ
    GLCall(program = glCreateProgram());//��������
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);//������ɫ��
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //����ɫ��������
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));//����
    GLCall(glValidateProgram(program));//��֤

    //ɾ����ɫ��(��ɫ�����Ѿ����)
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

int Shader::GetUniformLocation(const std::string& name)//�������
{
    if (m_UniformlocationCache.find(name) != m_UniformlocationCache.end()) {
        return m_UniformlocationCache[name];
    }
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
    }

    m_UniformlocationCache[name] = location;
    return location;
}
