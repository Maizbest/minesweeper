#include "utils.h"
#include <iostream>

namespace utils
{
    void normalizeSizes(GLFWwindow *window, float &width, float &height)
    {
        int iw, ih;
        glfwGetWindowSize(window, &iw, &ih);

        width = width / (float)iw;
        height = height / (float)ih;
    };

    glm::vec2 normalizeCoords(GLFWwindow *window, glm::vec2 coords)
    {
        int iw, ih;
        glfwGetWindowSize(window, &iw, &ih);
        return glm::vec2(coords.x / (float)iw - 1.0f, coords.y / (float)iw + 1.0f);
    };
    void print(glm::vec2 vec)
    {
        std::cout << "(" << vec.x << "," << vec.y << ");" << std::endl;
    }
} // namespace utils
