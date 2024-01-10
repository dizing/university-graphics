#pragma once

#include "Interfaces.h"

namespace my_graph_lib {

class tPoint : public Figure {
 public:
  tPoint();
  tPoint(Position position, RGBColor color, float size);

  void Draw(Drawer &) override;
  void MoveBy(Position) override;

  void setPosition(Position);
  Position getPosition() const;

  void setRGBColor(RGBColor);
  RGBColor getRGBColor() const;

  void setSize(float radius);
  float getSize() const;

 private:
  Position position_;
  float size_;
  RGBColor color_;
};

}  // namespace my_graph_lib
