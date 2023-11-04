#pragma once
#include <tuple>
#include <vector>

namespace my_graph_lib {

using RGBColor = std::tuple<uint8_t, uint8_t, uint8_t>;
using Position = std::tuple<float, float>;

struct AbstractPointDrawer {
  virtual void Draw(Position, RGBColor, float) = 0;
  virtual ~AbstractPointDrawer() {}
};

class tPoint {
 public:
  tPoint();
  tPoint(Position position, RGBColor color, float size);

  void Draw(AbstractPointDrawer&);

  void setPosition(Position);
  Position getPosition() const;

  void setRGBColor(RGBColor);
  RGBColor getRGBColor() const;

  void setSize(float radius);
  float getSize() const;

  void movePointBy(Position delta);

 private:
  Position position_;
  float size_;
  RGBColor color_;
};

}  // namespace my_graph_lib
