#pragma once
#include <vector>

#include "DrawInterfaces.h"

namespace my_graph_lib {

class tSegmentFigure : public Drawable {
 public:
  void Draw(Drawer &) override;

  void setRGBColor(RGBColor);
  RGBColor getRGBColor() const;
  const std::vector<Position> &getPoints() const;

  static void movePointBy(tSegmentFigure &figure, Position delta);

 protected:
  tSegmentFigure(std::vector<Position> points, RGBColor color);

 private:
  std::vector<Position> points_;
  RGBColor color_;
};

}  // namespace my_graph_lib