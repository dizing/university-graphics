#pragma once

#include "tSegmentFigure.h"

namespace my_graph_lib {
class tRectangle : public tSegmentFigure {
 public:
  tRectangle(Position pos_a, Position pos_b, Position pos_c, Position pos_d,
             RGBColor color);
};

}  // namespace my_graph_lib