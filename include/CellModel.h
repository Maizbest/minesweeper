#ifndef B6B8D351_CC98_4665_BA5F_EA266DED979D
#define B6B8D351_CC98_4665_BA5F_EA266DED979D

#include "meshes.h"
#include <GLFW/glfw3.h>

class CellModel
{
private:
    RectangleMesh *rect;
    LineMesh *line1;
    LineMesh *line2;
    TriangleMesh *light;
    TriangleMesh *shadow;

public:
    CellModel(GLFWwindow *w);
    ~CellModel();
    void draw(Shader &shader);
    void unbind();
};

#endif /* B6B8D351_CC98_4665_BA5F_EA266DED979D */
