
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "libgl.h"
#include "shader_s.h"

#define ASSERT(x)                                                                                                      \
    if (!(x))                                                                                                          \
        __debugbreak();

#define GLCall(x)                                                                                                      \
    GLClearError();                                                                                                    \
    x;                                                                                                                 \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

GLFWwindow *window = nullptr;

struct Vertex;

GLuint createTriangle();
void framebuffer_size_callback(GLFWwindow *w, int width, int height);
void processInput();
void init();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

static bool GLLogCall(const char *func, const char *file, int line)
{
    while (GLenum err = glGetError())
    {
        std::cout << "[OpenGL] " << file << " line " << line << " call " << func << " ERROR: " << err << std::endl;
        return false;
    }
    return true;
}

int main()
{
    init();

    if (!window)
        return -1;

    Shader shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");

    auto triangle = createTriangle();

    while (!glfwWindowShouldClose(window))
    {
        processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(triangle);

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &triangle);
    // glDeleteBuffers(1, &/);

    glfwTerminate();
    return 0;
}

void init()
{
    if (glfwInit())
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwTerminate();
        }
    }
}

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
};

GLuint createTriangle()
{
    std::vector<Vertex> vertices = {Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
                                    Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
                                    Vertex{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}};

    unsigned int vboID, vaoID;
    GLCall(glGenVertexArrays(1, &vaoID));
    GLCall(glGenBuffers(1, &vboID));
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    return vaoID;
}

void processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *w, int width, int height)
{
    glViewport(0, 0, width, height);
}