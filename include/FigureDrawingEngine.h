#pragma once
#include "FigureDrawingMenu.h"
#include "tPoint.h"
#include "tRectangle.h"
#include "tTriangle.h"
#include <functional>

class MovablePointState {
public:
    MovablePointState() {}

    void handleEvents(sf::Event event) {
        static const std::map <sf::Keyboard::Key, std::function<int(int)>> press_handlers {
            {sf::Keyboard::Left, [](int flags) {return flags | kLeft; }},
            {sf::Keyboard::Right, [](int flags) {return flags | kRight; }},
            {sf::Keyboard::Up, [](int flags) {return flags | kUp; }},
            {sf::Keyboard::Down, [](int flags) {return flags | kDown; }},
            {sf::Keyboard::R, [](int flags) {return flags | kRandom; }}
        };
        static const std::map <sf::Keyboard::Key, std::function<int(int)>> release_handlers{
            {sf::Keyboard::Left, [](int flags) {return flags & ~kLeft; }},
            {sf::Keyboard::Right, [](int flags) {return flags & ~kRight; }},
            {sf::Keyboard::Up, [](int flags) {return flags & ~kUp; }},
            {sf::Keyboard::Down, [](int flags) {return flags & ~kDown; }},
            {sf::Keyboard::R, [](int flags) {return flags & ~kRandom; }}
        };
        
        if (event.type == sf::Event::KeyPressed) {
            direction_flags_ = press_handlers.at(event.key.code)(direction_flags_);
        }
        if (event.type == sf::Event::KeyReleased) {
            direction_flags_ = release_handlers.at(event.key.code)(direction_flags_);
        }
    }
    
    struct inside_pos {
        float x;
        float y;

        inside_pos& operator+=(const inside_pos& other) {
            x += other.x;
            y += other.y;
            return *this;
        }
        inside_pos operator+(const inside_pos& other) {
            inside_pos tmp = *this;
            tmp += other;
            return tmp;
        }
    };

    my_graph_lib::Position GetUpdateDelta() {
        inside_pos delta = { 0, 0 };
        static const std::vector<std::function<void(int, inside_pos&)>> updaters{
            [](int flags, inside_pos& delta) {if (flags & kLeft) delta.x -= 10.f; },
            [](int flags, inside_pos& delta) {if (flags & kRight) delta.x += 10.f; },
            [](int flags, inside_pos& delta) {if (flags & kUp) delta.y -= 10.f; },
            [](int flags, inside_pos& delta) {if (flags & kDown) delta.y += 10.f; },
            [](int flags, inside_pos& delta) {if (flags & kRandom) delta += { (rand() % 6) - 2.5f, (rand() % 6) - 2.5f }; },
        };
        for (auto& updater : updaters) {
            updater(direction_flags_, delta);
        }
        return { delta.x, delta.y };
    }

private: 
    enum MovingDirections
    {
        kLeft = 1 << 0, // binary 00001
        kRight = 1 << 1, // binary 00010
        kUp = 1 << 2, // binary 00100
        kDown = 1 << 3,  // binary 01000
        kRandom = 1 << 4  // binary 10000
    };
    int direction_flags_ = 0;
};

using Drawables =
    std::map<std::string, std::unique_ptr<my_graph_lib::Drawable>>;
Drawables InitializeDrawables() {
  Drawables drawables;
  my_graph_lib::RGBColor color = {rand() % 255, rand() % 255, rand() % 255};
  std::array<my_graph_lib::Position, 4> points = {
      {{300.f, 300.f}, {500.f, 500.f}, {300.f, 500.f}, {500.f, 300.f}}};
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
          my_graph_lib::tPoint::movePointBy(
              dynamic_cast<my_graph_lib::tPoint&>(
                  *drawables_[current_drawable_object_name_]),
              movable_state_.GetUpdateDelta());
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