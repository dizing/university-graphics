#pragma once
#include <cstdint>
#include <tuple>

namespace my_graph_lib {

class tPoint;
class tSegmentFigure;
class tLineSegment;
class tCircle;
class tEllipse;

using RGBColor = std::tuple<uint8_t, uint8_t, uint8_t>;
struct Position {
  float x;
  float y;

  Position &operator+=(const Position &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  Position operator+(const Position &other) { return Position(*this) += other; }
};

struct Drawer {
  virtual void Draw(const tPoint &) = 0;
  virtual void Draw(const tSegmentFigure &) = 0;
  virtual void Draw(const tLineSegment &) = 0;
  virtual void Draw(const tCircle &) = 0;
  virtual void Draw(const tEllipse &) = 0;
  virtual ~Drawer() {}
};

struct Drawable {
  virtual void Draw(Drawer &) = 0;
  virtual ~Drawable() {}
};
struct Movable {
  virtual void MoveBy(Position delta) = 0;
  virtual ~Movable() {}
};

struct Figure : public Drawable, public Movable {
  virtual ~Figure() {}
};
}  // namespace my_graph_lib