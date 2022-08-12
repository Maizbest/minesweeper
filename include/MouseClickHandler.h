#ifndef __MOUSECLICKHANDLER_H__
#define __MOUSECLICKHANDLER_H__

class MouseClickHandler
{
public:
    // pure virtual function
    virtual void handleMouseClick(float x, float y) = 0;
};

#endif // __MOUSECLICKHANDLER_H__