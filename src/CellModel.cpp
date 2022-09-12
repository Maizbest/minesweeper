#include "CellModel.h"

CellModel::CellModel(GLFWwindow *window)
{

    const glm::vec3 WHITE = glm::vec3(1.0f, 1.0f, 1.0f);
    const glm::vec3 BLACK = glm::vec3(0.0f, 0.0f, 0.0f);

    rect = new RectangleMesh(window, glm::vec2(0.1f, -0.1f), glm::vec2(0.9f, -0.9f), WHITE * 0.8f);

    line1 = new LineMesh(window, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, -1.0f), WHITE * 0.8f);

    shadow = new TriangleMesh(window,
                              glm::vec2(1.0f, 0.0f),
                              glm::vec2(1.0f, -1.0f),
                              glm::vec2(0.0f, -1.0f),
                              WHITE * 0.4f);
    light = new TriangleMesh(window,
                             glm::vec2(0.0f, 0.0f),
                             glm::vec2(1.0f, 0.0f),
                             glm::vec2(0.0f, -1.0f),
                             WHITE);
}

CellModel::~CellModel()
{
    this->unbind();
}

void CellModel::unbind()
{
    shadow->unbind();
    light->unbind();
    line1->unbind();
    rect->unbind();
}

void CellModel::draw(Shader &shader)
{
    shadow->draw(shader);
    light->draw(shader);
    line1->draw(shader);
    rect->draw(shader);
}
