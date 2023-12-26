#pragma once
#include <array>
#include <tuple>
#include <vector>

#include "DrawInterfaces.h"
#include "tSegmentFigure.h"

namespace my_graph_lib {
class tRectangle : public tSegmentFigure {
 public:
  tRectangle(Position pos_a, Position pos_b, Position pos_c, Position pos_d,
             RGBColor color)
      : tSegmentFigure({pos_a, pos_b, pos_c, pos_d}, color) {}
};

}  // namespace my_graph_lib