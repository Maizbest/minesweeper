#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
  VertexArray();
  ~VertexArray();

  void AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout);
  void Bind() const;
  void Unbind() const;

private:
  unsigned int m_RendererID;
};

#endif // __VERTEXARRAY_H__