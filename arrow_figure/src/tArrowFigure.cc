#include "tArrowFigure.h"

tArrowFigure::tArrowFigure() {
    my_graph_lib::tEllipse ellipse({50, 50}, {0, 0, 0}, 20, 5, 1.5f);
    ellipse.setFillColor({255,255,204});
    drawing_pieces_.emplace_back(std::make_unique<my_graph_lib::tEllipse>(std::move(ellipse)));
    my_graph_lib::tEllipse inner_ellipse({60, 60},  {0, 0, 0}, 10, 5, 1.5f);
    inner_ellipse.setFillColor({255,255,255});
    drawing_pieces_.emplace_back(std::make_unique<my_graph_lib::tEllipse>(std::move(inner_ellipse)));
    my_graph_lib::tRectangle white_rectangle({100.0f,200.0f}, {40.0f,200.0f}, {40.0f,80.0f}, {100.0f,80.0f}, {255,255,255});
    white_rectangle.setFillColor({255,255,255});
    drawing_pieces_.emplace_back(std::make_unique<my_graph_lib::tRectangle>(std::move(white_rectangle)));
    my_graph_lib::tRectangle black_left_rectangle({60.0f,85.0f}, {45.0f,85.0f}, {45.0f,80.0f}, {60.0f,80.0f}, {0,0,0});
    black_left_rectangle.setFillColor({0,0,0});
    drawing_pieces_.emplace_back(std::make_unique<my_graph_lib::tRectangle>(std::move(black_left_rectangle)));
    my_graph_lib::tTriangle triangle({75.0f,80.0f}, {100.0f,80.0f}, {87.5f,95.0f}, {0,0,0});
    triangle.setFillColor({255,255,204});
    drawing_pieces_.emplace_back(std::make_unique<my_graph_lib::tTriangle>(std::move(triangle)));
    my_graph_lib::tRectangle yellow_right_rectangle({85.0f,80.0f}, {90.0f,80.0f}, {85.0f,83.0f}, {90.0f,83.0f}, {255,255,204});
    yellow_right_rectangle.setFillColor({255,255,204});
    drawing_pieces_.emplace_back(std::make_unique<my_graph_lib::tRectangle>(std::move(yellow_right_rectangle)));
}

void tArrowFigure::Draw(SFMLDrawer& drawer) {
    for (auto& drawing_figure : drawing_pieces_) {
        drawing_figure->Draw(drawer);
    }
}

void tArrowFigure::MoveBy(my_graph_lib::Position delta) {
    for (auto& drawing_figure : drawing_pieces_) {
        drawing_figure->MoveBy(delta);
    }
}
