#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Vertex.h"
#include "utils.h"

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
    // unsigned int verticies;
    unsigned int shaderID;

public:
    // RectangleMesh(unsigned int shaderID);
    RectangleMesh(GLFWwindow *window, unsigned int shaderID, glm::vec2 position, uint32_t width, uint32_t height, glm::vec3 color);
    ~RectangleMesh();
    unsigned int getVAO();
    unsigned int getVBO();
    unsigned int getEBO();
    void unbind();
    void bindVAO();
    void draw();
    void move(glm::vec2);
};

RectangleMesh::RectangleMesh(GLFWwindow *w, unsigned int shaderID, glm::vec2 position, uint32_t width, uint32_t height, glm::vec3 color)
{
    // this->window = w;
    this->shaderID = shaderID;

    float nwidht = (float) width, nheight = (float) height;
    utils::normalizeSizes(w, nwidht, nheight);

    std::cout << "Normalized sizes: ";
    utils::print(glm::vec2(nwidht, nheight));

    glm::vec2 upLeft = utils::normalizeCoords(w, position);
    glm::vec2 upRight = glm::vec2(upLeft.x + nwidht, upLeft.y);
    glm::vec2 downLeft = glm::vec2(upLeft.x, upLeft.y - nheight);
    glm::vec2 downRight = glm::vec2(upLeft.x + nwidht, upLeft.y - nheight);

    utils::print(upLeft);
    utils::print(upRight);
    utils::print(downLeft);
    utils::print(downRight);

    std::vector<Vertex2d> vertices = {        // positions   // color coords
        Vertex2d::from(upRight, color),
        Vertex2d::from(downRight, color),
        Vertex2d::from(downLeft, color),
        Vertex2d::from(upLeft, color),
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
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

void RectangleMesh::draw()
{
    this->bindVAO();
    glBindVertexArray(VAO); // ITS IMPORTANT!!!!!
    glBindVertexArray(VAO); // ITS IMPORTANT!!!!!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // ITS IMPORTANT!!!!!
}

void RectangleMesh::move(glm::vec2 pos)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
}

void RectangleMesh::bindVAO()
{
    std::cout << "Bind vao=" << this->VAO << std::endl;
    glBindVertexArray(this->VAO);
}

void RectangleMesh::unbind()
{
    std::cout << "Undining mesh: vao=" << this->VAO << " vbo=" << this->VBO << std::endl;
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}

RectangleMesh::~RectangleMesh()
{
    unbind();
}

#endif