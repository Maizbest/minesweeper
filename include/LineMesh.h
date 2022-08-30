#ifndef __LINEMESH_H__
#define __LINEMESH_H__

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
#include "utils.h"

class LineMesh
{
private:

    unsigned int VBO, VAO, EBO;


public:
    LineMesh(GLFWwindow *w, glm::vec2 start, glm::vec2 end, glm::vec3 color);
    ~LineMesh();
    unsigned int getVAO();
    unsigned int getVBO();
    unsigned int getEBO();
    void unbind();
    void bindVAO();
    void draw(Shader &shader);
};

#endif // __LINEMESH_H__