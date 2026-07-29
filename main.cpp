#include <ctime>
#include <iostream>
#include "Game.h"
#include "GUI.h"

int32_t main() {
    srand(time(nullptr));
    GUI gui;
    gui.WindowMax();
    gui.FontSize(28);
    Game game;
    game.Run();
    return 0;
}
