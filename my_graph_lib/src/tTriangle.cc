#include "tTriangle.h"

namespace my_graph_lib {

tTriangle::tTriangle(Position pos_a, Position pos_b, Position pos_c,
                     RGBColor color)
    : tSegmentFigure({pos_a, pos_b, pos_c}, color) {}

} // namespace my_graph_lib