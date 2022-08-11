#ifndef CONTEXT_H
#define CONTEXT_H

class Context
{
private:
    unsigned int screenWidth, screenHeight;
public:
    Context(int height, int width) : screenWidth(width), screenHeight(height) {};
    ~Context();
    
};


Context::~Context()
{
}


#endif