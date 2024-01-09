#include "SFMLDrawer.h"

SFMLDrawer::SFMLDrawer(sf::RenderWindow &window) : window_(window) {}

void SFMLDrawer::Draw(const my_graph_lib::tPoint &point) {
  sf::CircleShape shape;

  auto [x, y] = point.getPosition();
  shape.setPosition(x, y);
  auto [r, g, b] = point.getRGBColor();
  shape.setFillColor({r, g, b});
  shape.setRadius(point.getSize());
  window_.draw(shape);
}

void SFMLDrawer::Draw(const my_graph_lib::tSegmentFigure &figure) {
  auto &points = figure.getPoints();
  auto [r, g, b] = figure.getRGBColor();
  sf::ConvexShape convex;
  convex.setPointCount(points.size());
  for (auto i = 0; i < points.size(); ++i) {
    auto &[x, y] = points[i];
    convex.setPoint(i, sf::Vector2f(x, y));
  }
  convex.setFillColor({r, g, b});
  window_.draw(convex);
}

void SFMLDrawer::Draw(const my_graph_lib::tLineSegment &segment) {
  auto &points = segment.getPoints();
  auto [r, g, b] = segment.getRGBColor();
  auto &[x0, y0] = points[0];
  auto &[x1, y1] = points[1];
  sf::VertexArray line(sf::LineStrip, 2);
  line[0] = sf::Vertex(sf::Vector2f(x0, y0), {r, g, b});
  line[1] = sf::Vertex(sf::Vector2f(x1, y1), {r, g, b});
  window_.draw(line);
}

void SFMLDrawer::Draw(const my_graph_lib::tCircle &circle) {
  sf::CircleShape shape;

  auto [x, y] = circle.getPosition();
  shape.setPosition(x, y);
  auto [r, g, b] = circle.getRGBColor();
  shape.setOutlineColor({r, g, b});
  shape.setRadius(circle.getSize());
  shape.setOutlineThickness(circle.getThickness());
  shape.setFillColor(sf::Color::Transparent);
  window_.draw(shape);
}

void SFMLDrawer::Draw(const my_graph_lib::tEllipse &ellipse) {
  sf::CircleShape shape;

  auto [x, y] = ellipse.getPosition();
  shape.setPosition(x, y);
  auto [r, g, b] = ellipse.getRGBColor();
  shape.setOutlineColor({r, g, b});
  shape.setRadius(ellipse.getSize());
  shape.setOutlineThickness(ellipse.getThickness());
  shape.setFillColor(sf::Color::Transparent);

  shape.setScale(1.0f, 1.0f * ellipse.getCoeff());

  window_.draw(shape);
}