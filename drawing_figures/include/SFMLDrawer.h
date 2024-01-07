#pragma once

#include <SFML/Graphics.hpp>

#include "DrawInterfaces.h"
#include "tLineSegment.h"
#include "tPoint.h"
#include "tRectangle.h"
#include "tTriangle.h"

class SFMLDrawer : public my_graph_lib::Drawer {
public:
  SFMLDrawer(sf::RenderWindow &window);

  void Draw(const my_graph_lib::tPoint &) override;
  void Draw(const my_graph_lib::tSegmentFigure &) override;
  void Draw(const my_graph_lib::tLineSegment &) override;

private:
  sf::RenderWindow &window_;
};