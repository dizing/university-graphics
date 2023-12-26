#pragma once
#include "FigureDrawingMenu.h"
#include "tPoint.h"
#include "tRectangle.h"
#include "tTriangle.h"

class MovablePointState {
 public:
  MovablePointState() {}

  void moveAccordingly(my_graph_lib::tPoint& point) {
    if (is_moving_left) {
      point.movePointBy({-10, 0});
    }
    if (is_moving_right) {
      point.movePointBy({10, 0});
    }
    if (is_moving_up) {
      point.movePointBy({0, -10});
    }
    if (is_moving_down) {
      point.movePointBy({0, +10});
    }
    if (is_moving_random) {
      point.movePointBy({(rand() % 6) - 2.5, (rand() % 6) - 2.5});
    }
  }
  void handleEvents(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Left) {
        is_moving_left = true;
      } else if (event.key.code == sf::Keyboard::Right) {
        is_moving_right = true;
      } else if (event.key.code == sf::Keyboard::Up) {
        is_moving_up = true;
      } else if (event.key.code == sf::Keyboard::Down) {
        is_moving_down = true;
      } else if (event.key.code == sf::Keyboard::R) {
        is_moving_random = !is_moving_random;
      }
    }
    if (event.type == sf::Event::KeyReleased) {
      if (event.key.code == sf::Keyboard::Left) {
        is_moving_left = false;
      } else if (event.key.code == sf::Keyboard::Right) {
        is_moving_right = false;
      } else if (event.key.code == sf::Keyboard::Up) {
        is_moving_up = false;
      } else if (event.key.code == sf::Keyboard::Down) {
        is_moving_down = false;
      }
    }
  }

  my_graph_lib::Position GetUpdateDelta() {
    if (is_moving_left) {
      return {-10, 0};
    }
    if (is_moving_right) {
      return {10, 0};
    }
    if (is_moving_up) {
      return {0, -10};
    }
    if (is_moving_down) {
      return {0, +10};
    }
    if (is_moving_random) {
      return {(rand() % 6) - 2.5, (rand() % 6) - 2.5};
    }
  }

 private:
  bool is_moving_right = false;
  bool is_moving_left = false;
  bool is_moving_up = false;
  bool is_moving_down = false;
  bool is_moving_random = false;
};

using Drawables =
    std::map<std::string, std::unique_ptr<my_graph_lib::Drawable>>;
Drawables InitializeDrawables() {
  Drawables drawables;
  my_graph_lib::RGBColor color = {rand() % 255, rand() % 255, rand() % 255};
  std::array<my_graph_lib::Position, 4> points = {
      {{300, 300}, {500, 500}, {300, 500}, {500, 300}}};
  my_graph_lib::tPoint point;
  point.setPosition(points[0]);
  point.setRGBColor(color);
  point.setSize(50);
  drawables["Point"] =
      std::move(std::make_unique<my_graph_lib::tPoint>((point)));
  drawables["Triangle"] = std::move(std::make_unique<my_graph_lib::tTriangle>(
      points[0], points[1], points[2], color));
  drawables["Rectangle"] = std::move(std::make_unique<my_graph_lib::tRectangle>(
      points[0], points[1], points[2], points[3], color));
  return drawables;
}

std::vector<std::string> GetDrawablesKeys(const Drawables& drawables) {
  std::vector<std::string> keys;
  for (auto& [key, _] : drawables) {
    keys.push_back(key);
  }
  return keys;
}

class FigureDrawingEngine : public MenuOwner {
 public:
  enum class EngineState { kMenu, kDrawingObject };
  FigureDrawingEngine(sf::RenderWindow& window, sf::Font font)
      : menu_(*this, font, GetDrawablesKeys(drawables_)) {
    current_state_ = EngineState::kMenu;
    menu_.SetSize(window.getSize().x, window.getSize().y);
  }

  void OnEvent(sf::Event event) {
    if (current_state_ == EngineState::kMenu) {
      menu_.OnEvent(event);
    } else {
      if (event.key.code == sf::Keyboard::Escape) {
        current_state_ = EngineState::kMenu;
        return;
      }
      movable_state_.handleEvents(event);
    }
  }
  void Draw(sf::RenderWindow& window, my_graph_lib::Drawer& drawer) {
    if (current_state_ == EngineState::kMenu) {
      menu_.Draw(window);
    }
    if (current_state_ == EngineState::kDrawingObject) {
      drawables_[current_drawable_object_name_]->Draw(drawer);
    }
  }

  void Update() {
    if (current_state_ == EngineState::kDrawingObject) {
      if (current_drawable_object_name_ == "Point") {
        movable_state_.moveAccordingly(dynamic_cast<my_graph_lib::tPoint&>(
            *drawables_[current_drawable_object_name_]));
      }
      if (current_drawable_object_name_ == "Rectangle") {
        my_graph_lib::tRectangle::movePointBy(
            dynamic_cast<my_graph_lib::tRectangle&>(
                *drawables_[current_drawable_object_name_]),
            movable_state_.GetUpdateDelta());
      }
      if (current_drawable_object_name_ == "Triangle") {
        my_graph_lib::tTriangle::movePointBy(
            dynamic_cast<my_graph_lib::tTriangle&>(
                *drawables_[current_drawable_object_name_]),
            movable_state_.GetUpdateDelta());
      }
    }
  }

  void SetSize(float x, float y) { menu_.SetSize(x, y); }

  virtual void OnMenuItemSelected(std::string selected_item_name) override {
    current_drawable_object_name_ = selected_item_name;
    current_state_ = EngineState::kDrawingObject;
  }

  virtual void OnMenuExited() override {}

 private:
  Drawables drawables_ = InitializeDrawables();
  std::string current_drawable_object_name_;
  FigureDrawingMenu menu_;
  MovablePointState movable_state_;
  EngineState current_state_;
};