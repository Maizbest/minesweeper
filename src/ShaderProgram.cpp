#include "ShaderProgram.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>


#include "Renderer.h"

ShaderProgram::ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath)
{
    unsigned int vertex = CompileShader(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragment = CompileShader(fragmentPath, GL_FRAGMENT_SHADER);

    // shader Program
    GLCall(m_RendererID = glCreateProgram());
    GLCall(glAttachShader(m_RendererID, vertex));
    GLCall(glAttachShader(m_RendererID, fragment));
    GLCall(glLinkProgram(m_RendererID));
    CheckCompileErrors(m_RendererID, "PROGRAM");


    glDeleteShader(vertex);
    glDeleteShader(fragment);
    std::cout << "shader program created." << std::endl;
}

ShaderProgram::~ShaderProgram()
{
    std::cout << "Delete shader program" << std::endl;
    GLCall(glDeleteProgram(m_RendererID));
};

unsigned int ShaderProgram::CompileShader(const std::string& shaderPath, GLenum type)
{
    // vertex shader
    std::string shaderCode = ParseShader(shaderPath);
    const char* code = shaderCode.c_str(); // how to not do that?
    std::cout << "Compiling shader." << std::endl;
    GLCall(unsigned int shader = glCreateShader(type));
    GLCall(glShaderSource(shader, 1, &code, NULL));
    GLCall(glCompileShader(shader));
    CheckCompileErrors(shader, type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
    return shader;
}

std::string ShaderProgram::ParseShader(const std::string &shaderPath)
{
    if (!std::filesystem::exists(shaderPath))
    {
        std::cout << "Vertex2d shader not found at " << std::filesystem::canonical(shaderPath);
    }
    std::string shaderCode;
    std::ifstream fStream;
    fStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        std::stringstream buffer;
        fStream.open(shaderPath);
        buffer << fStream.rdbuf();
        shaderCode = buffer.str();
    }
    catch (std::ifstream::failure &e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }
    return shaderCode;
}

void ShaderProgram::Bind()
{
    GLCall(glUseProgram(m_RendererID));
}

void ShaderProgram::Unbind()
{
    GLCall(glUseProgram(0));
}

void ShaderProgram::SetBool(const std::string &name, bool value)
{
    GLCall(glUniform1i(GetUniformLocation(name), (int)value));
}

void ShaderProgram::setInt(const std::string &name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void ShaderProgram::SetFloat(const std::string &name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void ShaderProgram::SetMat4(const std::string &name, const glm::mat4 &mat)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

void ShaderProgram::SetVec3(const std::string &name, const glm::vec3 &vec)
{
    GLCall(glUniform3fv(GetUniformLocation(name), 1, &(vec.x)));
}

int ShaderProgram::GetUniformLocation(const std::string &uniform)
{
    if (m_UniformLocationCache.find(uniform) != m_UniformLocationCache.end())
        return m_UniformLocationCache[uniform];
    GLCall(int location = glGetUniformLocation(m_RendererID, uniform.c_str()));
    m_UniformLocationCache[uniform] = location;
    return location;
}
// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void ShaderProgram::CheckCompileErrors(unsigned int shader, const std::string &type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
