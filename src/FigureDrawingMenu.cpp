#include "FigureDrawingMenu.h"

FigureDrawingMenu::FigureDrawingMenu(MenuOwner& owner, sf::Font font,
                                     std::vector<std::string> menu_content)
    : owner_(owner), current_item_(0), font_(std::move(font)) {
  for (auto& str : menu_content) {
    sf::Text text(str, font_);
    text.setFillColor({0, 0, 0});
    MenuElement item(std::move(text));
    item.setOutlineColor({203, 7, 23});
    item.setOutlineThickness(0);
    menu_items_.push_back(item);
  }
  SetSize(0, 0);
  ColorizeSelected(current_item_);
}

void FigureDrawingMenu::Draw(sf::RenderWindow& window) {
  for (auto& item : menu_items_) {
    item.Draw(window);
  }
}

void FigureDrawingMenu::SetSize(float x, float y) {
  for (int i = 0; i < menu_items_.size(); ++i) {
    menu_items_[i].setSize({x / 2.f, y / (menu_items_.size() * 2 + 1.f)});
    menu_items_[i].setPosition(
        x / 2. - menu_items_[i].getSize().x / 2.,
        (1. + 2. * i) * y / (menu_items_.size() * 2. + 1.f));
  }
}

void FigureDrawingMenu::OnEvent(sf::Event event) {
  if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Up) {
    current_item_ =
        (current_item_ != 0) ? current_item_ - 1 : menu_items_.size() - 1;
    ColorizeSelected(current_item_);
  }
  if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down) {
    current_item_ =
        (current_item_ != menu_items_.size() - 1) ? current_item_ + 1 : 0;
    ColorizeSelected(current_item_);
  }
  if (event.type == event.KeyReleased &&
      event.key.code == sf::Keyboard::Enter) {
    owner_.OnMenuItemSelected(menu_items_[current_item_].GetName());
  }
  if (event.type == event.KeyReleased &&
      event.key.code == sf::Keyboard::Escape) {
    owner_.OnMenuExited();
  }
}

void FigureDrawingMenu::ColorizeSelected(std::size_t new_selected) {
  for (auto& item : menu_items_) {
    item.setOutlineThickness(0);
  }
  menu_items_[new_selected].setOutlineThickness(10);
}