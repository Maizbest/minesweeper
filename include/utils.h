#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace utils
{
    void normalizeSizes(GLFWwindow *w, float &width, float &height);
    glm::vec2 normalizeCoords(GLFWwindow *window, glm::vec2 coords);
    void print(glm::vec2);
};

#endif