#ifndef CONTEXT_H
#define CONTEXT_H

#include <GLFW/glfw3.h>

class Context
{
private:
    GLFWwindow *window;
    unsigned int screenWidth, screenHeight;
public:
    Context(int height, int width) : screenWidth(width), screenHeight(height) {};
    ~Context();
    
};


Context::~Context()
{
}


#endif