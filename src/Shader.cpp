#include "Head/Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Head/Renderer.h"

Shader::Shader(const std::string& filepath)
    :m_FilePath(filepath), m_RendererID(0)
{
    /* 从文件中解析着色器源码 */
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));//启用渲染
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));//启用0地址（无渲染器）
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

    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));//往shader里输入变量
}

void Shader::SetUniforMath4f (const std::string& name,const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);//判断是否能打开文件
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };//枚举shader类型

    std::string line;//shaer代码的每一行
    std::stringstream ss[2];//string流(用来保存shader的代码)
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) //找到着色器
        {
            if (line.find("vertex") != std::string::npos)//找到顶点着色器
            {
                type = ShaderType::VERTEX;//进入vertex流
            }
            else if (line.find("fragment") != std::string::npos) //找到片元着色器
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';//输入代码
        }
    }
    return { ss[0].str(),ss[1].str() };//返回两个流
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id;
    GLCall(id = glCreateShader(type));//创建对应的shader
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));//设置源码
    GLCall(glCompileShader(id));//编译shader

    //错误处理
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); // 获取当前着色器编译状态
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length)); // 获取日志长度
        char* msg = (char*)alloca(length * sizeof(char)); //生成日志数组
        GLCall(glGetShaderInfoLog(id, length, &length, msg)); // 获取日志信息
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << msg << std::endl;
        GLCall(glDeleteShader(id)); // 删除着色器
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program;//程序标识
    GLCall(program = glCreateProgram());//创建程序
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);//编译着色器
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //绑定着色器到程序
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));//链接
    GLCall(glValidateProgram(program));//验证

    //删除着色器(着色程序已经完成)
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

int Shader::GetUniformLocation(const std::string& name)//输入参数
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
