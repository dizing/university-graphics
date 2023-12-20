#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include <vector>
#include <string>

class FigureDrawingMenu {
    public:
    FigureDrawingMenu(float x, float y, sf::Font font, std::vector<std::string> menu_content) : current_item_(0), font_(std::move(font)) {
        for (auto& str : menu_content) {
            sf::Text text(str, font_);
            text.setFillColor({0, 0, 0});
            MenuElement item(std::move(text));
            item.setOutlineColor({203, 7, 23});
            item.setOutlineThickness(0);
            menu_items_.push_back(item);
        }
        Resize(x, y);
        ColorizeSelected(current_item_);
    }
    void Draw(sf::RenderWindow& window) {
        for (auto& item : menu_items_) {
            item.Draw(window);
        }
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
            ColorizeSelected(current_item_);
        }
        if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down) {
            current_item_ = (current_item_ != menu_items_.size() - 1) ? current_item_ + 1 : 0;
            ColorizeSelected(current_item_);
        }
        if (event.KeyPressed && event.key.code == sf::Keyboard::Enter) {
            //parent_.changeState()
        }
    }

    private:

    class MenuElement : public sf::RectangleShape {
        public:
        MenuElement(sf::Text text) : sf::RectangleShape(), text_(std::move(text)) {
        }
        void Draw(sf::RenderWindow& window) {
            window.draw(static_cast<sf::RectangleShape>(*this));
            window.draw(text_);
        }
        void setPosition(float x, float y) {
            sf::RectangleShape::setPosition(x, y);
            text_.setPosition(x, y);
        }
        void setSize(const sf::Vector2f &size) {
            sf::RectangleShape::setSize(size);
            text_.setCharacterSize((size.y > 10) ? size.y - 10 : 1);
        }

        private:
        sf::Text text_;
    };

    std::vector<MenuElement> menu_items_{};
    std::size_t current_item_;
    sf::Font font_;

    void ColorizeSelected(std::size_t new_selected) {
        for (auto& item : menu_items_) {
            item.setOutlineThickness(0);
        }
        menu_items_[new_selected].setOutlineThickness(10);
    }
};



// class FigureDrawingEngine {
//     public:

//     enum class State {
//         kMenu,
//         kMovableObject
//      };
    
//     FigureDrawingEngine();
//     void OnEvent(sf::Event event);
//     void Draw(my_graph_lib::Drawer&);

//     private:
//     FigureDrawingMenu menu_;

// };