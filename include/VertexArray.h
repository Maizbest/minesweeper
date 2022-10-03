#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
  VertexArray();
  // VertexArray(VertexArray &&) = default;
  // VertexArray(const VertexArray &) = default;
  // VertexArray &operator=(VertexArray &&) = default;
  // VertexArray &operator=(const VertexArray &) = default;
  ~VertexArray();

  void AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout);
  void Bind() const;
  void Unbind() const;

private:
  unsigned int m_RendererID;
};

#endif // __VERTEXARRAY_H__