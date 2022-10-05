
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

GLFWwindow *window = nullptr;

struct Vertex
{
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 texture;
};

void framebuffer_size_callback(GLFWwindow *w, int width, int height);
void processInput();
void init();

const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;

int main()
{
  init();

  if (!window)
    return -1;

  {
    std::vector<Vertex> vertices = {
        Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(100.0f, 100.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(100.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3};

    // GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    VertexArray va;
    VertexBufferLayout layout;
    VertexBuffer vb(vertices.data(), sizeof(Vertex) * vertices.size());

    layout.Push<float>(3); // position
    layout.Push<float>(3); // color
    layout.Push<float>(2); // texture
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(100.0f, 100.0f, 0.0f));
    glm::mat4 model(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    
    ShaderProgram shaderProgram("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");
    shaderProgram.Bind();

    Texture tex("resources/textures/doge.png");
    tex.Bind();
    shaderProgram.SetInt("u_Texture", 0);
    shaderProgram.SetMat4("u_MVP", proj * view * model);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    tex.Unbind();
    shaderProgram.Unbind();

    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
      processInput();

      GLCall(glClearColor(0.0, 0.6, 0.1, 1.0));

      renderer.Clear();

      shaderProgram.Bind();
      shaderProgram.SetFloat("time", glfwGetTime());

      tex.Bind();
      renderer.Draw(va, ib, shaderProgram);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }
  glfwTerminate();
  return 0;
}

void init()
{
  if (glfwInit())
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cout << "Failed to initialize GLAD" << std::endl;
      glfwTerminate();
    }
  }
}

void processInput()
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *w, int width, int height)
{
  GLCall(glViewport(0, 0, width, height));
}