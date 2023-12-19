#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "DrawInterfaces.h"

#include <vector>
#include <string>

class FigureDrawingMenu {
    public:
    FigureDrawingMenu(float x, float y) : current_item_(0) {
        for (auto& str : {"Point", "Line", "Segment", "Rectangle", "Triangle"}) {
            sf::RectangleShape shape;
            menu_items_.push_back(shape);
        }
        for (auto& item : menu_items_) {
            item.setOutlineColor({203, 7, 23});
            item.setOutlineThickness(0);
        }
        Resize(x, y);
    }
    void Draw(sf::RenderWindow& window) {
        ColorizeSelected(current_item_);
        for (auto& item : menu_items_) {
            window.draw(item);
        }
        sf::Font font{};
        font.loadFromFile("/Users/julietah/Documents/SIBSUTIS/ООП/university_graphics/src/ethn.otf");
        sf::Text text("HHH", font);
        window.draw(text);
    }

    void Resize(float x, float y) {
         for (int i = 0; i < menu_items_.size(); ++i) {
            menu_items_[i].setSize({x / 2.f, y / (menu_items_.size() * 2 + 1.f)});
            menu_items_[i].setPosition(x / 2. - menu_items_[i].getSize().x / 2., (1. + 2. * i) * y / (menu_items_.size() * 2. + 1.f));
         }
    }

    void OnEvent(sf::Event event) {
        if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Up) {
            current_item_ = (current_item_ != 0) ? current_item_ - 1 : menu_items_.size() - 1;
        }
        if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down) {
            current_item_ = (current_item_ != menu_items_.size() - 1) ? current_item_ + 1 : 0;
        }
        if (event.KeyPressed && event.key.code == sf::Keyboard::Enter) {
            //parent_.changeState()
        }
    }

    private:
    std::vector<sf::RectangleShape> menu_items_{};
    std::size_t current_item_;

    void ColorizeSelected(std::size_t new_selected) {
        for (auto& item : menu_items_) {
            item.setOutlineThickness(0);
        }
        menu_items_[new_selected].setOutlineThickness(10);
    }
};



class FigureDrawingEngine {
    public:

    enum class State {
        kMenu,
        kMovableObject
     };
    
    FigureDrawingEngine();
    void OnEvent(sf::Event event);
    void Draw(my_graph_lib::Drawer&);

    private:
    FigureDrawingMenu menu_;

};