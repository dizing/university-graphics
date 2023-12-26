#include "tSegmentFigure.h"

namespace my_graph_lib {

int orientation(Position p, Position q, Position r) {
  auto &[pX, pY] = p;
  auto &[qX, qY] = q;
  auto &[rX, rY] = r;
  int val = (qY - pY) * (rX - qX) - (qX - pX) * (rY - qY);

  if (val == 0) return 0;
  return (val > 0) ? 1 : 2;
}

tSegmentFigure::tSegmentFigure(std::vector<Position> points, RGBColor color)
    : points_(),
      color_(std::move(color))

{
  int l = 0;
  for (int i = 1; i < points.size(); i++)
    if (std::get<0>(points[i]) < std::get<0>(points[l])) l = i;
  int p = l, q;
  do {
    points_.push_back(points[p]);
    q = (p + 1) % points.size();
    for (int i = 0; i < points.size(); i++) {
      if (orientation(points[p], points[i], points[q]) == 2) q = i;
    }
    p = q;
  } while (p != l);
}

const std::vector<Position> &tSegmentFigure::getPoints() const {
  return points_;
}

void tSegmentFigure::Draw(Drawer &drawer) { drawer.Draw(*this); }

void tSegmentFigure::setRGBColor(RGBColor new_color) { color_ = new_color; }

RGBColor tSegmentFigure::getRGBColor() const { return color_; }

void tSegmentFigure::movePointBy(tSegmentFigure &figure, Position delta) {
  auto [delta_x, delta_y] = delta;
  for (auto &pos : figure.points_) {
    pos = {std::get<0>(pos) + delta_x, std::get<1>(pos) + delta_y};
  }
}

}  // namespace my_graph_lib