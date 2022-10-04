
#include "IndexBuffer.h"
#include "Renderer.h"
#include <iostream>

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_Count(count)
{
  ASSERT(sizeof(unsigned int) == sizeof(GLuint));

  GLCall(glGenBuffers(1, &m_RendererID));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
  std::cout << "Delete index buffer" << std::endl;
  GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind()
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind()
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
