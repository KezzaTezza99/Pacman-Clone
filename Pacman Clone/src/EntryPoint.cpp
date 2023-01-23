#include "Engine/Graphics/GameWindow.h"
#include <iostream>

const int WIDTH = 1024;
const int HEIGHT = 768;

int main()
{
    GameWindow window("Pacman", WIDTH, HEIGHT);

    //Game loop
    while (!window.Closed())
    {
        window.Clear();

        window.Update();
    }
    return 0;
}