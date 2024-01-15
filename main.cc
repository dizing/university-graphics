#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "tArrowFigure.h"
#include "MovableObjectState.h"

int main() {
  srand(time(NULL));
  auto window = sf::RenderWindow{{600u, 400u}, "Drawing movable arrow"};
  window.setFramerateLimit(60);

  MovableObjectState state;
  SFMLDrawer drawer(window);
  tArrowFigure figure;
  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed ||
          event.type == sf::Event::KeyReleased) {
        state.OnEvent(event);
      }
      if (event.type == sf::Event::Resized) {
        window.setView(
            sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
      }
    }
    window.clear({255, 255, 255});
    figure.MoveBy(state.GetUpdateDelta());
    figure.Draw(drawer);

    window.display();
  }
}