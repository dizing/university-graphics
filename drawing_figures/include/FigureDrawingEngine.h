#pragma once
#include <functional>
#include <memory>

#include "FigureDrawingMenu.h"
#include "SFMLDrawer.h"

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

class FigureDrawingEngine : public MenuOwner {
 public:
  enum class EngineState { kMenu, kDrawingObject };

  using Drawables =
      std::map<std::string, std::unique_ptr<my_graph_lib::Drawable>>;

  FigureDrawingEngine(sf::RenderWindow &window, sf::Font font);

  void OnEvent(sf::Event event);

  void Draw(sf::RenderWindow &window);

  void Update();

  void SetSize(float x, float y);

  virtual void OnMenuItemSelected(std::string selected_item_name) override;
  virtual void OnMenuExited() override;

 private:
  Drawables drawables_ = InitializeDrawables();
  std::string current_drawable_object_name_;
  FigureDrawingMenu menu_;
  MovableObjectState movable_state_;
  EngineState current_state_;
  SFMLDrawer drawer_;

  Drawables InitializeDrawables();

  std::vector<std::string> GetDrawablesKeys(const Drawables &drawables);
};