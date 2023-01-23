#ifndef __GAME_WINDOW__
#define __GAME_WINDOW__
#include <glew.h>
#include <glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

class GameWindow
{
private:
	//Window variables
	const char* m_title;
	int m_width, m_height;
	GLFWwindow* m_window;
	bool m_closed;

	//User input
	bool m_keys[MAX_KEYS];
	bool m_mouseButtons[MAX_BUTTONS];			//Game won't need mouse but just implementing it anyway
	double m_x, m_y;

public:
	//Methods for the window
	GameWindow(const char* title, int width, int height);
	~GameWindow();
	bool Closed() const;
	void Update();
	void Clear() const;

	//Methods for user input
	bool IsKeyPressed(unsigned int keyCode) const;
	bool IsMouseButtonPressed(unsigned int button) const;
	void GetMousePosition(double& x, double& y) const;

	//Usefull getter methods
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

private:
	bool InitialisedGLFW();
	//Callback functions required by GLFW
	friend static void window_resize(GLFWwindow* window, int width, int height);
	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
};
#endif // !__GAME_WINDOW__

