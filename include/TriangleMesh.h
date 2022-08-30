#ifndef BFFAE61B_3F43_4C95_9971_FC8C0884DECA
#define BFFAE61B_3F43_4C95_9971_FC8C0884DECA

#include "shader_s.h" // includes glad

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "minesweeper/Vertex2d.h"

class TriangleMesh
{
private:
    unsigned int VBO, VAO, EBO;

public:
    // RectangleMesh(unsigned int shaderID);
    TriangleMesh(GLFWwindow *w, glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec3 color);
    ~TriangleMesh();
    unsigned int getVAO();
    unsigned int getVBO();
    unsigned int getEBO();
    void unbind();
    void bindVAO();
    void draw(Shader &shader);
};

#endif /* BFFAE61B_3F43_4C95_9971_FC8C0884DECA */
