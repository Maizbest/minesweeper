#ifndef D005C26F_C593_4FEF_97C1_085ADCA68645
#define D005C26F_C593_4FEF_97C1_085ADCA68645

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

class ShaderProgram
{
  private:
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

  public:
    ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);
    ~ShaderProgram();

    void Bind();
    void Unbind();

    void SetBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void SetFloat(const std::string &name, float value);
    void SetMat4(const std::string &name, const glm::mat4 &mat);
    void SetVec3(const std::string &name, const glm::vec3 &vec);

  private:
    std::string ParseShader(const std::string &shaderPath);
    unsigned int CompileShader(const std::string &shaderPath, GLenum type);
    int GetUniformLocation(const std::string &uniform);
    void CheckCompileErrors(unsigned int shader, const std::string &type);
};
#endif /* D005C26F_C593_4FEF_97C1_085ADCA68645 */
