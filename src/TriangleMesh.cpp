#include "TriangleMesh.h"

// #include "minesweeper/Vertex2d.h"
// #include "utils.h"


TriangleMesh::TriangleMesh(GLFWwindow *w, glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec3 color)
{
    std::vector<Vertex2d> vertices = {// positions   // color coords
                                      Vertex2d::from(a, color),
                                      Vertex2d::from(b, color),
                                      Vertex2d::from(c, color)};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2d) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), (void *)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void TriangleMesh::draw(Shader &shader)
{
    shader.use();
    this->bindVAO();
    glBindVertexArray(VAO); // ITS IMPORTANT!!!!!
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TriangleMesh::bindVAO()
{
    // std::cout << "Bind vao=" << this->VAO << std::endl;
    glBindVertexArray(this->VAO);
}

void TriangleMesh::unbind()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}

TriangleMesh::~TriangleMesh()
{
    unbind();
}
