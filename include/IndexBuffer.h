#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__

class IndexBuffer
{
  public:
    IndexBuffer(const unsigned int *data, unsigned int count);
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