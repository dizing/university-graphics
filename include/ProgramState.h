#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "DrawInterfaces.h"


class ProgramState {
    ProgramState();

    void OnEvent(sf::Event event);

    void Draw(my_graph_lib::Drawer&);
};