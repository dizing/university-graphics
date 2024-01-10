#pragma once

#include "tSegmentFigure.h"

namespace my_graph_lib {
class tLineSegment : public tSegmentFigure {
 public:
  tLineSegment(Position pos_a, Position pos_b, RGBColor color);

  void Draw(Drawer &drawer);
};

}  // namespace my_graph_lib