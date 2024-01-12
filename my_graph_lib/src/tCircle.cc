#include "tCircle.h"

namespace my_graph_lib {
tCircle::tCircle(Position position, RGBColor color, float size, float thickness)
    : thickness_(thickness), tPoint(position, color, size) {}

void tCircle::Draw(Drawer &drawer) { drawer.Draw(*this); }

float tCircle::getThickness() const { return thickness_; }

void tCircle::setThickness(float thickness) { thickness_ = thickness; }

void tCircle::setFillColor(RGBColor color) {
    fill_color_ = color;
}

std::optional<RGBColor> tCircle::getFillColor() const {
    return fill_color_;
}

}  // namespace my_graph_lib