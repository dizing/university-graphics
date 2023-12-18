#pragma once
#include <vector>

#include "DrawInterfaces.h"

namespace my_graph_lib {

class tSegmentFigure : public Drawable {
 public:
  void Draw(Drawer&) override;

  void setRGBColor(RGBColor);
  RGBColor getRGBColor() const;
  const std::vector<Position>& getPoints() const;

  protected: 
  tSegmentFigure(std::vector<Position> points, RGBColor color,
                 float line_thickness);
 private:
  std::vector<Position> points_;
  RGBColor color_;
  float line_thickness_;
};

}  // namespace my_graph_lib