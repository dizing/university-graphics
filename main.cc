#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "FigureDrawingEngine.h"

int main() {
  srand(time(NULL));
  auto window = sf::RenderWindow{{1500u, 700u}, "Drawable and movable figures"};
  window.setFramerateLimit(60);

  sf::Font font{};
#ifdef oop_sibsutis_RESOURCE_DIRECTORY
  font.loadFromFile(std::string(oop_sibsutis_RESOURCE_DIRECTORY) + "/font.otf");
#else
  static_assert(false, "Error in build system. Missing resource directory");
#endif
  FigureDrawingEngine engine(window, font);

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed ||
          event.type == sf::Event::KeyReleased) {
        engine.OnEvent(event);
      }
      if (event.type == sf::Event::Resized) {
        window.setView(
            sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        engine.SetSize(window.getSize().x, window.getSize().y);
      }
    }
    window.clear();

    engine.Update();
    engine.Draw(window);

    window.display();
  }
}