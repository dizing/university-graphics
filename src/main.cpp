#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>

#include "FigureDrawingEngine.h"
#include "FigureDrawingMenu.h"
#include "tPoint.h"
#include "tSegmentFigure.h"
#include "tTriangle.h"

class SFMLPointDrawer : public my_graph_lib::Drawer {
 public:
  SFMLPointDrawer(sf::RenderWindow& window) : window_(window) {}

  void Draw(const my_graph_lib::tPoint& point) override {
    sf::CircleShape shape;
    shape.setPosition(1, 2);
    auto [x, y] = point.getPosition();
    auto [r, g, b] = point.getRGBColor();
    shape.setPosition(x, y);
    shape.setFillColor({r, g, b});
    shape.setRadius(point.getSize());
    window_.draw(shape);
  }

  void Draw(const my_graph_lib::tSegmentFigure& figure) override {
    auto& points = figure.getPoints();
    auto [r, g, b] = figure.getRGBColor();
    if (points.size() > 2) {
      sf::ConvexShape convex;
      convex.setPointCount(points.size());
      for (auto i = 0; i < points.size(); ++i) {
        auto& [x, y] = points[i];
        convex.setPoint(i, sf::Vector2f(x, y));
      }
      convex.setFillColor({r, g, b});
      window_.draw(convex);
    } else {
      auto& [x0, y0] = points[0];
      auto& [x1, y1] = points[1];
      sf::VertexArray line(sf::LineStrip, 2);
      line[0] = sf::Vertex(sf::Vector2f(x0, y0), {r, g, b});
      line[1] = sf::Vertex(sf::Vector2f(x1, y1), {r, g, b});
      window_.draw(line);
    }
  }

 private:
  sf::RenderWindow& window_;
};

int main() {
  srand(time(NULL));
  auto window = sf::RenderWindow{{1920u, 1080u}, "CMake SFML Project"};
  window.setFramerateLimit(144);

  // std::vector<std::unique_ptr<my_graph_lib::Drawable>> drawables;
  // // СОЗДАТЬ 100 СЛУЧАЙНЫХ ТОЧЕК
  // for (int i = 0; i < 100; ++i) {
  //   my_graph_lib::Position pos = {fmodf(rand(), window.getSize().x),
  //                                 fmodf(rand(), window.getSize().y)};
  //   my_graph_lib::RGBColor color = {rand() % 255, rand() % 255, rand() %
  //   255}; float size = (rand() % 100) / 50.0f; drawables.push_back(
  //       std::make_unique<my_graph_lib::tPoint>(pos, color, size));
  // }
  // // СОЗДАТЬ СЛУЧАЙНЫЙ Треугольник
  //   std::array<my_graph_lib::Position, 3> points;
  //   for (int j = 0; j < 3; ++j) {
  //     points[j] = {fmodf(rand(), window.getSize().x),
  //                  fmodf(rand(), window.getSize().y)};
  //   }
  //   my_graph_lib::RGBColor color = {rand() % 255, rand() % 255, rand() %
  //   255}; float size = (rand() % 100) / 50.0f;
  //   drawables.push_back(std::make_unique<my_graph_lib::tTriangle>(
  //       points, color, size));
  SFMLPointDrawer drawer(window);
  // MovablePointState state;
  sf::Font font{};

  font.loadFromFile(
      "/Users/julietah/Documents/SIBSUTIS/ООП/university_graphics/src/"
      "ethn.otf");
  FigureDrawingEngine owner(window, font);
  // FigureDrawingMenu menu(owner, font,
  //                        {"Point", "Line", "Segment", "Rectangle",
  //                        "Triangle"});
  // menu.SetSize(window.getSize().x, window.getSize().y);

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed ||
          event.type == sf::Event::KeyReleased) {
        // state.handleEvents(event);
        // menu.OnEvent(event);
        owner.OnEvent(event);
      }
      if (event.type == sf::Event::Resized) {
        window.setView(
            sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        owner.SetSize(window.getSize().x, window.getSize().y);
      }
    }
    window.clear();
    // for (auto& drawable_figure : drawables) {
    //   drawable_figure->Draw(drawer);
    // }
    // state.moveAccordingly(main_point);
    // main_point.Draw(drawer);
    owner.Update();
    owner.Draw(window, drawer);
    // menu.Draw(window);

    window.display();
  }
}