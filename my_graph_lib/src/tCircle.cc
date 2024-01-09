#include "tCircle.h"

namespace my_graph_lib {
tCircle::tCircle(Position position, RGBColor color, float size, float thickness)
    : thickness_(thickness), tPoint(position, color, size) {}

void tCircle::Draw(Drawer &drawer) { drawer.Draw(*this); }

void tCircle::moveCircleBy(tCircle &circle, Position delta) {
  auto [x, y] = circle.getPosition();
  auto [delta_x, delta_y] = delta;
  circle.setPosition({x + delta_x, y + delta_y});
}

float tCircle::getThickness() const { return thickness_; }

void tCircle::setThickness(float thickness) { thickness_ = thickness; }

}  // namespace my_graph_lib