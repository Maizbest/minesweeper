
#include "minesweeper/MinesweeperGame.h"

void log(std::string text) {
    std::cout << text << std::endl;
}

Playfield::Playfield(GLFWwindow *window, int rows, int cols)
    : rows(rows), cols(cols), window(window), grid(Grid(window, cols, rows, 10.0, 10.0))
{
}

Playfield::~Playfield()
{
}

void Playfield::draw(Shader &shader)
{
    this->grid.draw(shader);
}

uint32_t Playfield::width()
{
    return 600;
}

uint32_t Playfield::height()
{
    return 600;
}

Menu::Menu(/* args */)
{
}

Menu::~Menu()
{
}

Stats::Stats(/* args */)
{
}

Stats::~Stats()
{
}

float Stats::getWidth()
{
    return this->width;
}

float Stats::getHeight()
{
    return this->height;
}

void Stats::draw(GLFWwindow *w, Shader &s) {}

int MinesweeperGame::createWindow(uint32_t width, uint32_t height)
{

    log("Creating window.");
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    this->window = glfwCreateWindow(width, height, "Minesweeper clone", NULL, NULL);
    if (window == NULL)
    {
        log("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(this->window);
    glfwSetCursorPosCallback(this->window, mouse_callback);
    glfwSetMouseButtonCallback(this->window, mouse_btn_callback);
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log("Failed to initialize GLAD");
        return -1;
    }
    return 0;
}

int MinesweeperGame::resize(uint32_t width, uint32_t height)
{
    glfwSetWindowSize(this->window, width, height);
    return 0;
}

int MinesweeperGame::displayMenu()
{
    return 0;
}

int MinesweeperGame::displayField()
{
    return 0;
}

MinesweeperGame::MinesweeperGame()
    : shader(Shader("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl")),
      state(GameState::PLAY)
{
    log("Instantiating game.");
    this->createWindow(100.0, 100.0);
    this->field = Playfield(this->window, 10, 10);
}

int MinesweeperGame::start()
{
    std::cout << "game started ..." << std::endl;
    while (!glfwWindowShouldClose(this->window))
    {
        if (GameState::PLAY == this->state)
        {
            std::cout << "Game in play state." << std::endl;
            this->resize(this->field.width(), this->stats.getHeight() + this->field.height());
            while (GameState::PLAY == this->state)
            {
                this->stats.draw(this->window, this->shader);
                this->field.draw(this->shader);
            }
        }
    }

    // remove all object
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void MinesweeperGame::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void MinesweeperGame::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void MinesweeperGame::mouse_btn_callback(GLFWwindow *window, int button, int action, int mods)
{

    // if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    // {

    //     for (auto &handler : MOUSE_CLICK_HANDLERS)
    //     {
    //         double xpos, ypos;
    //         glfwGetCursorPos(window, &xpos, &ypos);
    //         float x = (float)xpos, y = (float)ypos;
    //         utils::normalizeSizes(window, x, y);
    //         handler->handleMouseClick(x - 1, 1 - y);
    //     }
    // }
    // std::cout << "mouse pressed" << std::endl;
}

void MinesweeperGame::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
}
