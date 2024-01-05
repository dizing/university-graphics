#pragma once
#include <cstdint>
#include <tuple>

namespace my_graph_lib {

class tPoint;
class tSegmentFigure;

using RGBColor = std::tuple<uint8_t, uint8_t, uint8_t>;
struct Position {
  float x;
  float y;

  Position &operator+=(const Position &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  Position operator+(const Position &other) {
    Position tmp = *this;
    tmp += other;
    return tmp;
  }
};

struct Drawer {
  virtual void Draw(const tPoint &) = 0;
  virtual void Draw(const tSegmentFigure &) = 0;
  virtual ~Drawer() {}
};

struct Drawable {
  virtual void Draw(Drawer &) = 0;
  virtual ~Drawable() {}
};

} // namespace my_graph_lib