#ifndef A960CC21_227E_4489_B43F_0ABD1B998DAE
#define A960CC21_227E_4489_B43F_0ABD1B998DAE

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace utils
{
    void normalizeSizes(GLFWwindow *w, float &width, float &height);
    glm::vec2 normalizeCoords(GLFWwindow *window, glm::vec2 coords);
    void print(glm::vec2);
};

#endif /* A960CC21_227E_4489_B43F_0ABD1B998DAE */
