#pragma once

#include "tPoint.h"

namespace my_graph_lib {

class tCircle : public tPoint {
 public:
  tCircle(Position position, RGBColor color, float size, float thickness);

  void Draw(Drawer &) override;

  static void moveCircleBy(tCircle &circle, Position delta);

  float getThickness() const;
  void setThickness(float);

 private:
  float thickness_;
};

}  // namespace my_graph_lib