#include "utils.h"
#include <iostream>

namespace utils
{
    void normalizeSizes(GLFWwindow *window, float &width, float &height)
    {
        int iw, ih;
        glfwGetWindowSize(window, &iw, &ih);

        width = 2.0 * width / (float)iw;
        height = 2.0 * height / (float)ih;
    };

    // top left corner is 0, 0 coordinate
    glm::vec2 normalizeCoords(GLFWwindow *window, glm::vec2 coords)
    {

        // 600 600
        int iw, ih;
        glfwGetWindowSize(window, &iw, &ih);




        // for example we want 100 100
        // we must get 

        return glm::vec2(coords.x / (float)iw - 1.0f, coords.y / (float)iw + 1.0f);
    };
    void print(glm::vec2 vec)
    {
        std::cout << "(" << vec.x << "," << vec.y << ");" << std::endl;
    }
} // namespace utils
