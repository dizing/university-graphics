#pragma once
#include <vector>

#include "DrawInterfaces.h"

namespace my_graph_lib {

class tSegmentFigure : public Drawable {
 public:
  tSegmentFigure(std::vector<Position> points, RGBColor color,
                 float line_thickness);
  const std::vector<Position>& getPoints() const;
  void Draw(Drawer&) override;

  void setRGBColor(RGBColor);
  RGBColor getRGBColor() const;

 private:
  std::vector<Position> points_;
  RGBColor color_;
  float line_thickness_;
};

}  // namespace my_graph_lib