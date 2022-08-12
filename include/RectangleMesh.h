#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Vertex.h"
#include "utils.h"
#include "shader_s.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

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
    ~RectangleMesh();
    unsigned int getVAO();
    unsigned int getVBO();
    unsigned int getEBO();
    void unbind();
    void bindVAO();
    void draw(Shader &shader);
};

RectangleMesh::RectangleMesh(GLFWwindow *w, glm::vec3 color)
{

    std::vector<Vertex2d> vertices = {        // positions   // color coords
        Vertex2d::from(glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
        Vertex2d::from(glm::vec2(1.0f, 0.0f), color),
        Vertex2d::from(glm::vec2(0.0f, -1.0f), color),
        Vertex2d::from(glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
    };

    // 0 1
    // 2 3
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        0, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2d) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void RectangleMesh::draw(Shader &shader)
{
    shader.use();
    this->bindVAO();
    glBindVertexArray(VAO); // ITS IMPORTANT!!!!!
    glBindVertexArray(VAO); // ITS IMPORTANT!!!!!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // ITS IMPORTANT!!!!!
}

void RectangleMesh::bindVAO()
{
    // std::cout << "Bind vao=" << this->VAO << std::endl;
    glBindVertexArray(this->VAO);
}

void RectangleMesh::unbind()
{
    // std::cout << "Undining mesh: vao=" << this->VAO << " vbo=" << this->VBO << std::endl;
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}

RectangleMesh::~RectangleMesh()
{
    unbind();
}

#endif