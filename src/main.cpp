
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "Renderer.h"
#include "libgl.h"
#include "shader_s.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

GLFWwindow *window = nullptr;

struct Vertex
{
  glm::vec3 position;
  glm::vec3 color;
};

void framebuffer_size_callback(GLFWwindow *w, int width, int height);
void processInput();
void init();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
  init();

  if (!window)
    return -1;

  std::vector<Vertex> vertices = {
      Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
      Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
      Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
      Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
  };

  unsigned int indices[] = {
      0, 1, 2,
      0, 2, 3};

  {
    Shader shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");

    VertexArray va;
    VertexBufferLayout layout;
    VertexBuffer vb(vertices.data(), sizeof(Vertex) * vertices.size());
    layout.Push<float>(3); // position
    layout.Push<float>(3); // color
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    while (!glfwWindowShouldClose(window))
    {
      processInput();

      GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
      GLCall(glClear(GL_COLOR_BUFFER_BIT));

      shader.use();
      shader.setFloat("time", glfwGetTime());

      va.Bind();
      vb.Bind();
      ib.Bind();

      GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    GLCall(glDeleteProgram(shader.ID));
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

void processInput()
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *w, int width, int height)
{
  glViewport(0, 0, width, height);
}