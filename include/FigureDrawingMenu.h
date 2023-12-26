#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <string>
#include <vector>

struct MenuOwner {
  virtual void OnMenuItemSelected(std::string selected_item_name) = 0;
  virtual void OnMenuExited() = 0;
  virtual ~MenuOwner(){};
};

class FigureDrawingMenu {
 public:
  FigureDrawingMenu(MenuOwner& owner, sf::Font font,
                    std::vector<std::string> menu_content);

  void Draw(sf::RenderWindow& window);
  void SetSize(float x, float y);
  void OnEvent(sf::Event event);

 private:
  class MenuElement : public sf::RectangleShape {
   public:
    MenuElement(sf::Text text) : sf::RectangleShape(), text_(std::move(text)) {}
    void Draw(sf::RenderWindow& window) {
      window.draw(static_cast<sf::RectangleShape>(*this));
      window.draw(text_);
    }
    void setPosition(float x, float y) {
      sf::RectangleShape::setPosition(x, y);
      text_.setPosition(x, y);
    }
    void setSize(const sf::Vector2f& size) {
      sf::RectangleShape::setSize(size);
      text_.setCharacterSize((size.y > 15) ? size.y - 15 : 1);
    }
    std::string GetName() { return text_.getString(); }

   private:
    sf::Text text_;
  };

  MenuOwner& owner_;
  std::vector<MenuElement> menu_items_{};
  std::size_t current_item_;
  sf::Font font_;

  void ColorizeSelected(std::size_t new_selected);
};
