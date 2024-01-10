#pragma once
#include <vector>

#include "Interfaces.h"

namespace my_graph_lib {

class tSegmentFigure : public Figure {
 public:
  void Draw(Drawer &) override;
  void MoveBy(Position) override;

  void setRGBColor(RGBColor);
  RGBColor getRGBColor() const;
  const std::vector<Position> &getPoints() const;

 protected:
  tSegmentFigure(std::vector<Position> points, RGBColor color);

 private:
  std::vector<Position> points_;
  RGBColor color_;
};

}  // namespace my_graph_lib