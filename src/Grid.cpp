#include "Grid.h"


Grid::Grid(GLFWwindow *window, uint32_t width, uint32_t height, float cellWidth, float cellHeight)
    : cellWidth(cellWidth), cellHeight(cellHeight)
{
    this->window = window;
    this->width = width;
    this->height = height;
    this->cellModel = new CellModel(window);

    utils::normalizeSizes(this->window, this->cellWidth, this->cellHeight);
    // std::cout << "Grid cell: " << this->cellWidth << "x" << this->cellHeight << std::endl;

    this->cellPositions = std::vector<glm::vec2>(width * height);
    auto nextPos = glm::vec2(-1.0f, 1.0f);

    for (unsigned int row = 0; row < this->height; row++)
    {
        for (unsigned int col = 0; col < this->width; col++)
        {
            this->cellPositions[row * width + col] = nextPos;
            nextPos = glm::vec2(nextPos.x + this->cellWidth, nextPos.y);
        }
        nextPos = glm::vec2(-1.0, nextPos.y - this->cellHeight);
    }

    // std::cout << "Grid initialized: " << this->cells.size() << std::endl;
    // for (auto &cell : this->cells)
    // {
    //     std::cout << "Cell position: " << cell.position.x << " " << cell.position.y << std::endl;
    // }
}

Grid::~Grid()
{
    this->unbind();
}

void Grid::draw(Shader &shader)
{
    auto model = glm::mat4(1.0f);
    auto scale = glm::vec3(this->cellWidth, this->cellHeight, 1.0f);
    for (auto &position : this->cellPositions)
    {
        // std::cout << "Drawing cell" << std::endl;
        // std::cout << cell.position.x << " " << cell.position.y << std::endl;
        shader.setMat4("projection", glm::scale(glm::translate(model, glm::vec3(position, 0.0f)), scale));
        cellModel->draw(shader);
        shader.setMat4("projection", model);
    }
}

void Grid::unbind()
{
    cellModel->unbind();
}

void Grid::handleMouseClick(float x, float y)
{
    this->clickedx = x / this->cellWidth;
    this->clickedy = y / this->cellHeight;

    std::cout << "Grid handled mouse click event at (" << this->clickedx << ", " << this->clickedy << ")" << std::endl;
}
