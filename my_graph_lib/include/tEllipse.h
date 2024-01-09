#pragma once

#include "tCircle.h"

namespace my_graph_lib
{

    class tEllipse : public tCircle {
    public:
    tEllipse(Position position, RGBColor color, float size, float thickness, float coeff);

    void Draw(Drawer &) override;

    static void moveEllipseBy(tEllipse &ellipse, Position delta);

    float getCoeff() const;
    void setCoeff(float);    

    private:
    float coeff_;
};
    
} // namespace my_graph_lib


