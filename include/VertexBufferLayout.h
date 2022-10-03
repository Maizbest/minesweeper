#ifndef __VERTEXBUFFERLAYOUT_H__
#define __VERTEXBUFFERLAYOUT_H__

#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int GetTypeSize(unsigned int type)
  {
    switch (type)
    {
    case GL_FLOAT:
      return 4;
    case GL_UNSIGNED_INT:
      return 4;
    case GL_UNSIGNED_BYTE:
      return 1;
    }
    ASSERT(false);
    return 0;
  }
};

class VertexBufferLayout
{
private:
  std::vector<VertexBufferElement> m_Elements;
  unsigned int m_Stride;

public:
  VertexBufferLayout() : m_Stride(0){};
  ~VertexBufferLayout(){};

  inline unsigned int GetStride() const { return m_Stride; };
  inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }

  template <typename T>
  void Push(unsigned int count)
  {
    // static_assert(false);
    ASSERT(false);
  }
};

template <>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
  m_Elements.push_back(VertexBufferElement{GL_FLOAT, count, GL_FALSE});
  m_Stride += VertexBufferElement::GetTypeSize(GL_FLOAT) * count;
}

template <>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
  m_Elements.push_back(VertexBufferElement{GL_UNSIGNED_INT, count, GL_FALSE});
  m_Stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT) * count;
}

template <>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
  m_Elements.push_back(VertexBufferElement{GL_UNSIGNED_BYTE, count, GL_FALSE});
  m_Stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
}

#endif // __VERTEXBUFFERLAYOUT_H__