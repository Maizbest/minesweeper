
#include "IndexBuffer.h"
#include "Renderer.h"
#include <iostream>

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_Count(count)
{
  ASSERT(sizeof(unsigned int) == sizeof(GLuint));
  std::cout << "Create IBO" << std::endl;
  GLCall(glGenBuffers(1, &m_RendererID));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
  GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind()
{
std::cout << "Bind IBO" << std::endl;
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind()
{
  std::cout << "Unbind IBO" << std::endl;
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
