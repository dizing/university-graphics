#include "tEllipse.h"

namespace my_graph_lib
{

    
    tEllipse::tEllipse(Position position, RGBColor color, float size, float thickness, float coeff) : coeff_(coeff), tCircle(position, color, size, thickness){

    }

    void tEllipse::Draw(Drawer & drawer) {
        drawer.Draw(*this);
    }

    void tEllipse::moveEllipseBy(tEllipse &ellipse, Position delta) {
        auto [x, y] = ellipse.getPosition();
  auto [delta_x, delta_y] = delta;
  ellipse.setPosition({x + delta_x, y + delta_y});
    }

    float tEllipse::getCoeff() const {
    return coeff_;
}

    void tEllipse::setCoeff(float coeff) {
        coeff_ = coeff;
    }
  
} // namespace my_graph_lib

