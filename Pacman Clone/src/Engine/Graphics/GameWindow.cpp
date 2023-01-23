#include "GameWindow.h"
#include <iostream>

//Redefining the GLFW callbacks defined as friends to keep compiler happy
void window_resize(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

GameWindow::GameWindow(const char* title, int width, int height) 
    : m_title(title), m_width(width), m_height(height)
{
    if (!InitialisedGLFW())
        glfwTerminate;

    //Initialising the arrays used for Input
    for (int i = 0; i < MAX_KEYS; i++) { m_keys[i] = false; }
    for (int i = 0; i < MAX_BUTTONS; i++) { m_mouseButtons[i] = false; }
}

GameWindow::~GameWindow()
{
    glfwTerminate();
}

bool GameWindow::Closed() const
{
    return glfwWindowShouldClose(m_window);
}

void GameWindow::Update()
{
    //Want to check for any errors before updating 
    GLenum errors = glGetError();
    if (errors != GL_NO_ERROR)
        std::cout << "OpenGL Error: " << errors << std::endl;

    //Update
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

void GameWindow::Clear() const
{
    //Clearing the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool GameWindow::IsKeyPressed(unsigned int keyCode) const
{
    if (keyCode >= MAX_KEYS)
        return false;
    return m_keys[keyCode];
}

bool GameWindow::IsMouseButtonPressed(unsigned int button) const
{
    if (button >= MAX_BUTTONS)
        return false;
    return m_mouseButtons[button];
}

void GameWindow::GetMousePosition(double& x, double& y) const
{
    x = m_x;
    y = m_y;
}

bool GameWindow::InitialisedGLFW()
{
    // Checking to see if GLFW was initialised sucessfully
    if (!glfwInit())
    {
        std::cout << "Failed to initialise GLFW" << std::endl;
        return false;
    }

    //Creating a window 
    m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

    //Checking to see if the window was created succesfully or not
    if (!m_window)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        return false;
    }

    //Creating the current window context
    glfwMakeContextCurrent(m_window);
    glfwMakeContextCurrent(m_window);
    //Need a pointer to window for key handling
    glfwSetWindowUserPointer(m_window, this);
    //Allows for window resizing
    glfwSetWindowSizeCallback(m_window, window_resize);
    //Allows for keyboard call backs 
    glfwSetKeyCallback(m_window, key_callback);
    //Allows for mouse call backs 
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    //Allows for mouse cursor callbacks
    glfwSetCursorPosCallback(m_window, cursor_position_callback);

    //Disabling VSYNC
    glfwSwapInterval(0);

    //Checking to see if GLEW initialised correctly
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return false;
    }
    return true;
}

//GLFW Callback functions
void window_resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    GameWindow* gameWindow = (GameWindow*)glfwGetWindowUserPointer(window);
    gameWindow->m_keys[key] = action != GLFW_RELEASE;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    GameWindow* gameWindow = (GameWindow*)glfwGetWindowUserPointer(window);
    gameWindow->m_mouseButtons[button] = action != GLFW_RELEASE;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    GameWindow* gameWindow = (GameWindow*)glfwGetWindowUserPointer(window);
    gameWindow->m_x = xpos;
    gameWindow->m_y = ypos;
}
