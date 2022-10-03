#include "Renderer.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool GLLogCall(const char *func, const char *file, int line)
{
    while (GLenum err = glGetError())
    {
        std::cout << "[OpenGL] " << file << " line " << line << " call " << func << " ERROR: " << err << std::endl;
        return false;
    }
    return true;
}