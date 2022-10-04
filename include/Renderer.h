#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "libgl.h"

#define ASSERT(x)                                                                                                      \
    if (!(x))                                                                                                          \
        __debugbreak(); // is it portable?

#define GLCall(x)                                                                                                      \
    GLClearError();                                                                                                    \
    x;                                                                                                                 \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();

bool GLLogCall(const char *func, const char *file, int line);

#endif // __RENDERER_H__