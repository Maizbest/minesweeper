#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__

class IndexBuffer
{
  public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    // VertexBuffer(VertexBuffer &&) = default; // move
    // VertexBuffer(const VertexBuffer &) = default; // copy
    // VertexBuffer &operator=(VertexBuffer &&) = default; // move assignment
    // VertexBuffer &operator=(const VertexBuffer &) = default; // copy assigned
    ~IndexBuffer();

    void Bind();
    void Unbind();

    inline unsigned int GetCount() const
    {
        return m_Count;
    };

  private:
    unsigned int m_RendererID;
    unsigned int m_Count;
};

#endif // __INDEXBUFFER_H__