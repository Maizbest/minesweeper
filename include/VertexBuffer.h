#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

class VertexBuffer
{
  public:
    VertexBuffer(const void* data, unsigned int size);
    // VertexBuffer(VertexBuffer &&) = default; // move
    // VertexBuffer(const VertexBuffer &) = default; // copy
    // VertexBuffer &operator=(VertexBuffer &&) = default; // move assignment
    // VertexBuffer &operator=(const VertexBuffer &) = default; // copy assigned
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

  private:
    unsigned int m_RendererID;
};

#endif // __VERTEXBUFFER_H__