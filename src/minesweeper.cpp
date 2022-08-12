#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

#include "MouseClickHandler.h"
#include "shader_s.h"
#include "RectangleMesh.h"
#include "LineMesh.h"
#include "Grid.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_btn_callback(GLFWwindow *window, int button, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

const glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 GREEN = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 WHITE = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 BLACK = glm::vec3(0.0f, 0.0f, 0.0f);

static std::vector<MouseClickHandler *> mouseClickHandlers;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_btn_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl"); // you can name your shader files however you like
    Grid grid(window, 20, 20);
    mouseClickHandlers.push_back(&grid);
    // mouseClickHandlers.push_back((MouseClickEvent)[&grid](float x, float y){grid.handleMouseClick(x, y);});
    LineMesh yaxis(window, glm::vec2(0.0f, -1.0f), glm::vec2(0.0f, 1.0f), BLACK);
    LineMesh xaxis(window, glm::vec2(-1.0f, 0.0f), glm::vec2(1.0f, 0.0f), BLACK);

    // Shader shader("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
    // RectangleMesh rect(window, glm::vec2(0.0f, 0.0f), 10, 10, glm::vec3(1.0f, 0.0f, 0.0f));

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transformations
        // glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        // transform = glm::scale(transform,  glm::vec3(1.0f, 1.0f, 0.0f) * (1.0f - (float) sin((float)glfwGetTime()) * 0.5f));
        // transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        // render the triangle

        // rect1.move(glm::vec2((sin((float)glfwGetTime() - 0.05f * 3.14) + 1.0f) / 20.0f, 0.0f));
        // rect1.draw();

        // rect2.move(glm::vec2((sin((float)glfwGetTime() - 0.25f * 3.14) + 1.0f) / 20.0f, 0.0f));
        // rect2.draw();

        // rect2.move(glm::vec2((sin((float)glfwGetTime()) + 1.0f) / 20.0f, 0.0f));
        // rect3.draw();

        // shader.use();
        // rect.draw();
        grid.draw(shader);
        yaxis.draw(shader);
        xaxis.draw(shader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    grid.unbind();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_btn_callback(GLFWwindow *window, int button, int action, int mods)
{

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {

        for (auto &handler : mouseClickHandlers)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            float x = (float) xpos, y = (float) ypos;
            utils::normalizeSizes(window, x, y);
            // std::cout << "mouse: " << xpos - 1 << " " << 1 - ypos << std::endl;
            handler->handleMouseClick(x - 1, 1 - y);
        }
    }
    std::cout << "mouse pressed" << std::endl;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
}