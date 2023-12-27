#pragma once
#include <vector>

#include "DrawInterfaces.h"

namespace my_graph_lib {

class tPoint : public Drawable {
 public:
  tPoint();
  tPoint(Position position, RGBColor color, float size);

  void Draw(Drawer&) override;

  void setPosition(Position);
  Position getPosition() const;

  void setRGBColor(RGBColor);
  RGBColor getRGBColor() const;

  void setSize(float radius);
  float getSize() const;

  static void movePointBy(tPoint& point, Position delta);

 private:
  Position position_;
  float size_;
  RGBColor color_;
};

}  // namespace my_graph_lib
