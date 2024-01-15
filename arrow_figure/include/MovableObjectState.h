#pragma once
#include <SFML/Graphics.hpp>

#include "Interfaces.h"

class MovableObjectState {
 public:
  void OnEvent(sf::Event event);
  my_graph_lib::Position GetUpdateDelta();

 private:
  enum MovingDirections {
    kLeft = 1 << 0,
    kRight = 1 << 1,
    kUp = 1 << 2,
    kDown = 1 << 3,
    kRandom = 1 << 4
  };
  unsigned int direction_flags_ = 0;
};
