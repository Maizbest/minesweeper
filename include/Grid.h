#ifndef F4EFC172_C895_461B_BDB5_8AAABE1EE5B1
#define F4EFC172_C895_461B_BDB5_8AAABE1EE5B1

#include "shader_s.h" // includes glad
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

#include "MouseClickHandler.h"
#include "CellModel.h"

class Grid : public MouseClickHandler
{
private:
    CellModel *cellModel;
    GLFWwindow *window;
    uint32_t width, height;
    float cellWidth = 50.0f, cellHeight = 50.0f; // default

    uint32_t clickedx, clickedy;

    std::vector<glm::vec2> cellPositions;

public:
    Grid(){};
    Grid(GLFWwindow *window, uint32_t width, uint32_t height, float cellWidth, float cellHeight);
    ~Grid();
    // void mouseHover
    void draw(Shader &shader);
    void unbind();
    void handleMouseClick(float x, float y);
};

#endif /* F4EFC172_C895_461B_BDB5_8AAABE1EE5B1 */
