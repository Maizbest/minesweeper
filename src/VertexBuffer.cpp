#include "VertexBuffer.h"
#include <iostream>
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
  std::cout << "Create VBO" << std::endl;
  GLCall(glGenBuffers(1, &m_RendererID));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
  GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
  std::cout << "Bind VBO" << std::endl;
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
  std::cout << "Unbind VBO" << std::endl;
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
