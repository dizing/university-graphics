#pragma once

#include "tPoint.h"
#include "optional"


namespace my_graph_lib {

class tCircle : public tPoint {
 public:
  tCircle(Position position, RGBColor color, float size, float thickness);

  void Draw(Drawer &) override;

  float getThickness() const;
  void setThickness(float);

  void setFillColor(RGBColor color);
  std::optional<RGBColor> getFillColor() const;
  
 private:
  float thickness_;
  std::optional<RGBColor> fill_color_;
};

}  // namespace my_graph_lib