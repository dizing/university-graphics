#include "tLineSegment.h"

namespace my_graph_lib {
tLineSegment::tLineSegment(Position pos_a, Position pos_b, RGBColor color)
    : tSegmentFigure({pos_a, pos_b}, color) {}

void tLineSegment::Draw(Drawer &drawer) { drawer.Draw(*this); }

}  // namespace my_graph_lib