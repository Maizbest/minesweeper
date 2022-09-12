#ifndef D9AF8E4E_679C_43D9_868E_5CA9A55F1670
#define D9AF8E4E_679C_43D9_868E_5CA9A55F1670

#include <glm/glm.hpp>

struct Vertex2d
{
    float x = 0.0f, y = 0.0f, z = 0.0f;
    float r = 0.0f, g = 0.0f, b = 0.0f;

    static Vertex2d from(glm::vec2 pos, glm::vec3 color)
    {
        return Vertex2d{
            pos.x, pos.y, 0.0f, color.r, color.g, color.b};
    }
};


#endif /* D9AF8E4E_679C_43D9_868E_5CA9A55F1670 */
