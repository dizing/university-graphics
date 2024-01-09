#pragma once
#include <array>
#include <tuple>
#include <vector>

#include "DrawInterfaces.h"
#include "tSegmentFigure.h"

namespace my_graph_lib {
class tTriangle : public tSegmentFigure {
 public:
  tTriangle(Position pos_a, Position pos_b, Position pos_c, RGBColor color);
};

}  // namespace my_graph_lib