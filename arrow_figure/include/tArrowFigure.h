#pragma once

#include "SFMLDrawer.h"

class tArrowFigure : my_graph_lib::Movable {
    public:

    tArrowFigure();
    void Draw(SFMLDrawer& drawer);
    void MoveBy(my_graph_lib::Position delta);

    private:
    std::vector<std::unique_ptr<my_graph_lib::Figure>> drawing_pieces_;
};