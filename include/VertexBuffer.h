#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

class VertexBuffer
{
  public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

  private:
    unsigned int m_RendererID;
};

#endif // __VERTEXBUFFER_H__