#include "VertexArray.h"

#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>

VertexArray::VertexArray()
{
  std::cout << "Create VAO" << std::endl;
  GLCall(glGenVertexArrays(1, &m_RendererID));
  GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
  GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
  std::cout << "Bind VAO" << std::endl;
  glBindVertexArray(m_RendererID);
}
void VertexArray::Unbind() const
{
  std::cout << "Unbind VAO" << std::endl;
  glBindVertexArray(0);
};

void VertexArray::AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout)
{
  Bind();
  buffer.Bind();

  const auto &elements = layout.GetElements();

  uint64_t offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++)
  {
    const auto &elem = elements[i];

    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, layout.GetStride(), (const void *)offset);

    offset += elem.count * VertexBufferElement::GetTypeSize(elem.type);
  }
}
