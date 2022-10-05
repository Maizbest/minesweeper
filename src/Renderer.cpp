#include "Renderer.h"

#include <iostream>

void GLClearError()
{
  while (glGetError() != GL_NO_ERROR)
    ;
}

bool GLLogCall(const char *func, const char *file, int line)
{
  while (GLenum err = glGetError())
  {
    std::cout << "[OpenGL] " << file << " line " << line << " call " << func << " ERROR: " << err << std::endl;
    return false;
  }
  return true;
}


Renderer::Renderer(){};
Renderer::~Renderer(){};
void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const ShaderProgram &program) const
{
  program.Bind();

  va.Bind();
  ib.Bind();
  GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
};

void Renderer::Clear() const
{
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
