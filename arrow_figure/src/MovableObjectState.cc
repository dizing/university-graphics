#include "MovableObjectState.h"

void MovableObjectState::OnEvent(sf::Event event) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Left) direction_flags_ |= kLeft;
    if (event.key.code == sf::Keyboard::Right) direction_flags_ |= kRight;
    if (event.key.code == sf::Keyboard::Up) direction_flags_ |= kUp;
    if (event.key.code == sf::Keyboard::Down) direction_flags_ |= kDown;
    if (event.key.code == sf::Keyboard::R) direction_flags_ |= kRandom;
  }

  if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == sf::Keyboard::Left) direction_flags_ &= ~kLeft;
    if (event.key.code == sf::Keyboard::Right) direction_flags_ &= ~kRight;
    if (event.key.code == sf::Keyboard::Up) direction_flags_ &= ~kUp;
    if (event.key.code == sf::Keyboard::Down) direction_flags_ &= ~kDown;
    if (event.key.code == sf::Keyboard::R) direction_flags_ &= ~kRandom;
  }
}

my_graph_lib::Position MovableObjectState::GetUpdateDelta() {
  my_graph_lib::Position delta = {0, 0};

  if (direction_flags_ & kLeft) delta.x -= 10.f;
  if (direction_flags_ & kRight) delta.x += 10.f;
  if (direction_flags_ & kUp) delta.y -= 10.f;
  if (direction_flags_ & kDown) delta.y += 10.f;
  if (direction_flags_ & kRandom)
    delta += {(rand() % 6) - 2.5f, (rand() % 6) - 2.5f};

  return delta;
}