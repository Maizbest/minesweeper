#include "VertexBuffer.h"
#include <iostream>
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
  GLCall(glGenBuffers(1, &m_RendererID));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
  std::cout << "Delete vertex buffer" << std::endl;
  GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
