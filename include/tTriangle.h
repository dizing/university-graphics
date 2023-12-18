#pragma once
#include <tuple>
#include <vector>
#include <array>

#include "DrawInterfaces.h"
#include "tSegmentFigure.h"

namespace my_graph_lib {
class tTriangle : public tSegmentFigure {
    public: 
    tTriangle(std::array<Position, 3> positions,  RGBColor color, float line_thickness) : tSegmentFigure(std::vector(positions.begin(), positions.end()), color, line_thickness) {}
};

}  // namespace my_graph_lib