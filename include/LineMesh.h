#ifndef __LINEMESH_H__
#define __LINEMESH_H__


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

LineMesh::LineMesh(GLFWwindow *w, glm::vec2 start, glm::vec2 end, glm::vec3 color)
{
    // you can name your shader files however you like

    std::vector<Vertex2d> vertices = {        // positions   // color coords
        Vertex2d::from(start, color),
        Vertex2d::from(end, color),
    };

    // unsigned int indices[] = {
    //     0, 1
    // };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2d) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void LineMesh::draw(Shader &shader)
{
    shader.use();
    shader.setMat4("model", glm::mat4(1.0f));
    this->bindVAO();
    glBindVertexArray(VAO); // ITS IMPORTANT!!!!!
    glBindVertexArray(VAO); // ITS IMPORTANT!!!!!
    glDrawArrays(GL_LINES, 0, 2);
    // glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0); // ITS IMPORTANT!!!!!
}


void LineMesh::bindVAO()
{
    // std::cout << "Bind vao=" << this->VAO << std::endl;
    glBindVertexArray(this->VAO);
}

void LineMesh::unbind()
{
    // std::cout << "Undining mesh: vao=" << this->VAO << " vbo=" << this->VBO << std::endl;
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}

LineMesh::~LineMesh()
{
    unbind();
}


#endif // __LINEMESH_H__