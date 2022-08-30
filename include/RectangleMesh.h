#ifndef FF51CFC1_6C0D_4D30_B30A_A0D7D5192BA5
#define FF51CFC1_6C0D_4D30_B30A_A0D7D5192BA5

#include "shader_s.h" /// includes glad

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "minesweeper/Vertex2d.h"
#include "utils.h"

class RectangleMesh
{
private:
    // GLFWwindow *window;
    // int x, y;
    unsigned int cols = 10, rows = 10;

    unsigned int VBO, VAO, EBO;

public:
    // RectangleMesh(unsigned int shaderID);
    RectangleMesh(GLFWwindow *w, glm::vec3 color);
    RectangleMesh(GLFWwindow *w, glm::vec2 upperLeft, glm::vec2 lowerRight, glm::vec3 color);
    ~RectangleMesh();
    unsigned int getVAO();
    unsigned int getVBO();
    unsigned int getEBO();
    void unbind();
    void bindVAO();
    void draw(Shader &shader);
};

#endif /* FF51CFC1_6C0D_4D30_B30A_A0D7D5192BA5 */
