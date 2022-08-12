#ifndef GRID_H
#define GRID_H

#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

#include "RectangleMesh.h"
#include "utils.h"
#include "MouseClickHandler.h"

class Grid : public MouseClickHandler
{
private:
    RectangleMesh *cellMesh;
    GLFWwindow *window;
    unsigned int width, height;
    float cellWidth = 50.0f, cellHeight = 50.0f;
    uint32_t clickedx, clickedy;

public:
    Grid(GLFWwindow *window, float width, float height);
    ~Grid();
    // void mouseHover
    void draw(Shader &shader);
    void unbind();
    void handleMouseClick(float x, float y);
};

Grid::Grid(GLFWwindow *window, float width, float height)
{
    this->window = window;
    this->width = width;
    this->height = height;
    this->cellMesh = new RectangleMesh(window, glm::vec3(1.0f, 0.0f, 0.0f));
    utils::normalizeSizes(this->window, this->cellWidth, this->cellHeight);
    std::cout << "Grid cell: " << this->cellWidth << "x" << this->cellHeight << std::endl;
}

Grid::~Grid()
{
    this->unbind();
}

void Grid::draw(Shader &shader)
{
    auto model = glm::mat4(1.0f);
    auto nextPos = glm::vec2(-1.0f, 1.0f);
    for (unsigned int row = 0; row < this->height; row++)
    {
        for (unsigned int col = 0; col < this->width; col++)
        {
            // std::cout << col << " " << row << " at " << nextPos.x << " " << nextPos.y << std::endl;
            auto transform = model;
            transform = glm::translate(transform, glm::vec3(nextPos, 0.0f));
            transform = glm::scale(transform, glm::vec3(this->cellWidth * 0.95, this->cellHeight * 0.95, 1.0f));
            shader.setMat4("model", transform);
            cellMesh->draw(shader);

            nextPos = glm::vec2(nextPos.x + this->cellWidth, nextPos.y);
        }
        nextPos = glm::vec2(-1.0, nextPos.y - this->cellHeight);
    }
    // cellMesh->move(utils::normalizeCoords(this->window, glm::vec2((float)(row * cellHeight), -(float)(col * cellWidth))));
    // cellMesh->move(glm::vec2(0.1f, 0.1f));
    // cellMesh->draw();
}

void Grid::unbind()
{
    cellMesh->unbind();
}

void Grid::handleMouseClick(float x, float y)
{
    // uint32_t ux = (uint32_t) x, uy = (uint32_t) y;
    // uint32_t uw = (uint32_t) this->cellWidth, uh = (uint32_t) this->cellHeight;

    this->clickedx = x / this->cellWidth;
    this->clickedy = y / this->cellHeight;

    std::cout << "Grid handled mouse click event at (" << this->clickedx << ", " << this->clickedy << ")" << std::endl; 
}

#endif