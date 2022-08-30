#include "LineMesh.h"

LineMesh::LineMesh(GLFWwindow *w, glm::vec2 start, glm::vec2 end, glm::vec3 color)
{

    std::vector<Vertex2d> vertices = {        // positions   // color coords
        Vertex2d::from(start, color),
        Vertex2d::from(end, color),
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2d) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void LineMesh::draw(Shader &shader)
{
    shader.use();
    this->bindVAO();
    glBindVertexArray(VAO); // ITS IMPORTANT!!!!!
    glBindVertexArray(VAO); // ITS IMPORTANT!!!!!
    glDrawArrays(GL_LINES, 0, 2);
}


void LineMesh::bindVAO()
{
    glBindVertexArray(this->VAO);
}

void LineMesh::unbind()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}

LineMesh::~LineMesh()
{
    unbind();
}

