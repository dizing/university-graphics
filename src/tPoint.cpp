#include "tPoint.h"

namespace my_graph_lib {

tPoint::tPoint() {
  setPosition({0, 0});
  setRGBColor({0, 0, 0});
  setSize(1);
}

tPoint::tPoint(Position position, RGBColor color, float size) {
  setPosition(position);
  setRGBColor(color);
  setSize(size);
}

void tPoint::setPosition(Position position) { position_ = position; }

Position tPoint::getPosition() const { return position_; }

void tPoint::setRGBColor(RGBColor new_color) { color_ = new_color; }

RGBColor tPoint::getRGBColor() const { return color_; }

void tPoint::setSize(float radius) { size_ = radius; }

float tPoint::getSize() const { return size_; }

void tPoint::movePointBy(Position delta) {
  auto [x, y] = getPosition();
  auto [delta_x, delta_y] = delta;
  setPosition({x + delta_x, y + delta_y});
}

void tPoint::Draw(PointDrawer& drawer) {
  drawer.Draw(position_, color_, size_);
}

}  // namespace my_graph_lib