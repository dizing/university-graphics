#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <vector>

struct MenuOwner {
  virtual void OnMenuItemSelected(std::string selected_item_name) = 0;
  virtual void OnMenuExited() = 0;
  virtual ~MenuOwner(){};
};

class FigureDrawingMenu {
 public:
  FigureDrawingMenu(MenuOwner &owner, sf::Font font,
                    std::vector<std::string> menu_content);

  void Draw(sf::RenderWindow &window);
  void SetSize(float x, float y);
  void OnEvent(sf::Event event);

 private:
  class MenuElement;

  MenuOwner &owner_;
  std::vector<MenuElement> menu_items_;
  std::size_t current_item_;
  sf::Font font_;

  void ColorizeSelected(std::size_t new_selected);
};

class FigureDrawingMenu::MenuElement : public sf::RectangleShape {
 public:
  MenuElement(sf::Text text);
  void Draw(sf::RenderWindow &window);
  void setPosition(float x, float y);
  void setSize(const sf::Vector2f &size);
  std::string GetName();

 private:
  sf::Text text_;
};