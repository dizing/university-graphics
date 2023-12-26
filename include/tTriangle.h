#pragma once
#include <array>
#include <tuple>
#include <vector>

#include "DrawInterfaces.h"
#include "tSegmentFigure.h"

namespace my_graph_lib {
class tTriangle : public tSegmentFigure {
 public:
  tTriangle(Position pos_a, Position pos_b, Position pos_c, RGBColor color)
      : tSegmentFigure({pos_a, pos_b, pos_c}, color) {}
};

}  // namespace my_graph_lib