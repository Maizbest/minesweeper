#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "libgl.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

#define ASSERT(x) \
  if (!(x))       \
  __debugbreak() // is it portable?

#define GLCall(x) \
  GLClearError(); \
  x;              \
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *func, const char *file, int line);

class Renderer
{
public:
  Renderer();
  ~Renderer();
  void Draw(const VertexArray &va, const IndexBuffer &ib, const ShaderProgram &program) const;
  void Clear() const;
  // Renderer(Renderer &&) = default;
  // Renderer(const Renderer &) = default;
  // Renderer &operator=(Renderer &&) = default;
  // Renderer &operator=(const Renderer &) = default;

private:
};

#endif // __RENDERER_H__