#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>

#include "tPoint.h"

class SFMLPointDrawer : public my_graph_lib::AbstractPointDrawer {
 public:
  SFMLPointDrawer(sf::RenderWindow& window) : window_(window) {}

  void Draw(my_graph_lib::Position pos, my_graph_lib::RGBColor color,
            float radius) override {
    sf::CircleShape shape;
    shape.setPosition(1, 2);
    auto [x, y] = pos;
    auto [r, g, b] = color;
    shape.setPosition(x, y);
    shape.setFillColor({r, g, b});
    shape.setRadius(radius);
    window_.draw(shape);
  }

 private:
  sf::RenderWindow& window_;
};

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

 private:
  bool is_moving_right = false;
  bool is_moving_left = false;
  bool is_moving_up = false;
  bool is_moving_down = false;
  bool is_moving_random = false;
};

int main() {
  srand(time(NULL));
  auto window = sf::RenderWindow{{1920u, 1080u}, "CMake SFML Project"};
  window.setFramerateLimit(144);

  std::vector<my_graph_lib::tPoint> points;
  for (int i = 0; i < 100; ++i) {
    my_graph_lib::Position pos = {fmodf(rand(), window.getSize().x),
                                  fmodf(rand(), window.getSize().y)};
    my_graph_lib::RGBColor color = {rand() % 255, rand() % 255, rand() % 255};
    float size = (rand() % 100) / 50.0f;
    my_graph_lib::tPoint point(pos, color, size);
    points.push_back(std::move(point));
  }
  my_graph_lib::tPoint main_point;
  main_point.setPosition({500, 500});
  main_point.setRGBColor({100, 100, 100});
  main_point.setSize(50);
  SFMLPointDrawer drawer(window);
  MovablePointState state;
  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed ||
          event.type == sf::Event::KeyReleased) {
        state.handleEvents(event);
      }
    }
    window.clear();
    for (auto& point : points) {
      point.Draw(drawer);
    }
    state.moveAccordingly(main_point);
    main_point.Draw(drawer);
    window.display();
  }
}