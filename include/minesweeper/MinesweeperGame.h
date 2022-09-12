#ifndef _MINESWEEPER_CLASS_H_
#define _MINESWEEPER_CLASS_H_

#include <glad/glad.h>
#include "shader_s.h"
#include "Grid.h"
#include <GLFW/glfw3.h>

#include <math.h>
#include <iostream>
#include <vector>



enum GameState
{
    PLAY,
    MENU,
    GAMEOVER,
    WIN
};


struct Cell;

class Playfield
{
private:
    GLFWwindow *window;
    std::vector<Cell> cells;
    int rows, cols;
    Grid grid;

public:
    Playfield(GLFWwindow *window, int rows, int cols);
    Playfield(){};
    ~Playfield();
    void draw(Shader &shader);
    uint32_t width();
    uint32_t height();
};

enum CellState
{
    OPEN,
    CLOSED
};

enum CellMark
{
    NONE,
    FLAG,
    QUESTION
};

enum CellContent
{
    BOMB,
    COUNT,
    EMPTY
};

struct Cell
{
    CellState state;
    CellMark mark;
    CellContent content;
};

struct Button
{
    std::string text;
    bool pressed;
};

class Menu
{
private:
    Button small;
    Button medium;
    Button large;

public:
    Menu(/* args */);
    ~Menu();
};

class Stats
{
private:
    float width = 0.0, height = 0.0;
public:
    Stats(/* args */);
    ~Stats();
    void draw(GLFWwindow *w, Shader &shader);
    float getWidth();
    float getHeight();
};

class MinesweeperGame
{
private:
    GLFWwindow *window;
    Shader shader;

    GameState state;
    Playfield field;
    Stats stats;
    Menu menu;

    int createWindow(uint32_t width, uint32_t height);
    int resize(uint32_t width, uint32_t height);
    int displayMenu();
    int displayField();

    static void processInput(GLFWwindow *window);
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    static void mouse_btn_callback(GLFWwindow *window, int button, int action, int mods);
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);

public:
    MinesweeperGame();
    int start();
};

#endif /* _MINESWEEPER_CLASS_H_ */
