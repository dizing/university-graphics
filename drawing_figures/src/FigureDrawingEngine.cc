#include "FigureDrawingEngine.h"

void MovableObjectState::OnEvent(sf::Event event) {

  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Left)
      direction_flags_ |= kLeft;
    if (event.key.code == sf::Keyboard::Right)
      direction_flags_ |= kRight;
    if (event.key.code == sf::Keyboard::Up)
      direction_flags_ |= kUp;
    if (event.key.code == sf::Keyboard::Down)
      direction_flags_ |= kDown;
    if (event.key.code == sf::Keyboard::R)
      direction_flags_ |= kRandom;
  }

  if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == sf::Keyboard::Left)
      direction_flags_ &= ~kLeft;
    if (event.key.code == sf::Keyboard::Right)
      direction_flags_ &= ~kRight;
    if (event.key.code == sf::Keyboard::Up)
      direction_flags_ &= ~kUp;
    if (event.key.code == sf::Keyboard::Down)
      direction_flags_ &= ~kDown;
    if (event.key.code == sf::Keyboard::R)
      direction_flags_ &= ~kRandom;
  }
}

my_graph_lib::Position MovableObjectState::GetUpdateDelta() {
  my_graph_lib::Position delta = {0, 0};

  if (direction_flags_ & kLeft)
    delta.x -= 10.f;
  if (direction_flags_ & kRight)
    delta.x += 10.f;
  if (direction_flags_ & kUp)
    delta.y -= 10.f;
  if (direction_flags_ & kDown)
    delta.y += 10.f;
  if (direction_flags_ & kRandom)
    delta += {(rand() % 6) - 2.5f, (rand() % 6) - 2.5f};

  return delta;
}

FigureDrawingEngine::FigureDrawingEngine(sf::RenderWindow &window,
                                         sf::Font font)
    : menu_(*this, font, GetDrawablesKeys(drawables_)),
      current_drawable_object_name_(GetDrawablesKeys(drawables_)[0]),
      drawer_(window) {
  current_state_ = EngineState::kMenu;
  menu_.SetSize(window.getSize().x, window.getSize().y);
}

void FigureDrawingEngine::OnEvent(sf::Event event) {
  if (current_state_ == EngineState::kMenu) {
    menu_.OnEvent(event);
    return;
  }
  if (current_state_ == EngineState::kDrawingObject) {
    if (event.type == event.KeyReleased &&
        event.key.code == sf::Keyboard::Escape) {
      current_state_ = EngineState::kMenu;
      return;
    }
    movable_state_.OnEvent(event);
  }
}

void FigureDrawingEngine::Draw(sf::RenderWindow &window) {
  if (current_state_ == EngineState::kMenu) {
    menu_.Draw(window);
  }
  if (current_state_ == EngineState::kDrawingObject) {
    drawables_[current_drawable_object_name_]->Draw(drawer_);
  }
}

void FigureDrawingEngine::Update() {
  if (current_state_ == EngineState::kDrawingObject) {
    if (current_drawable_object_name_ == "Point") {
      my_graph_lib::tPoint::movePointBy(
          dynamic_cast<my_graph_lib::tPoint &>(
              *drawables_[current_drawable_object_name_]),
          movable_state_.GetUpdateDelta());
    }
    if (current_drawable_object_name_ == "Rectangle") {
      my_graph_lib::tRectangle::movePointBy(
          dynamic_cast<my_graph_lib::tRectangle &>(
              *drawables_[current_drawable_object_name_]),
          movable_state_.GetUpdateDelta());
    }
    if (current_drawable_object_name_ == "Triangle") {
      my_graph_lib::tTriangle::movePointBy(
          dynamic_cast<my_graph_lib::tTriangle &>(
              *drawables_[current_drawable_object_name_]),
          movable_state_.GetUpdateDelta());
    }
  }
}

void FigureDrawingEngine::SetSize(float x, float y) { menu_.SetSize(x, y); }

void FigureDrawingEngine::OnMenuItemSelected(std::string selected_item_name) {
  current_drawable_object_name_ = selected_item_name;
  current_state_ = EngineState::kDrawingObject;
}

void FigureDrawingEngine::OnMenuExited() {
  current_state_ = EngineState::kDrawingObject;
}

FigureDrawingEngine::Drawables FigureDrawingEngine::InitializeDrawables() {
  Drawables drawables;
  my_graph_lib::RGBColor color = {rand() % 255, rand() % 255, rand() % 255};
  std::array<my_graph_lib::Position, 4> points = {
      {{300.f, 300.f}, {500.f, 500.f}, {300.f, 500.f}, {500.f, 300.f}}};
  my_graph_lib::tPoint point;
  point.setPosition(points[0]);
  point.setRGBColor(color);
  point.setSize(50);
  drawables["Point"] =
      std::move(std::make_unique<my_graph_lib::tPoint>((point)));
  drawables["Triangle"] = std::move(std::make_unique<my_graph_lib::tTriangle>(
      points[0], points[1], points[2], color));
  drawables["Rectangle"] = std::move(std::make_unique<my_graph_lib::tRectangle>(
      points[0], points[1], points[2], points[3], color));
  return drawables;
}

std::vector<std::string> FigureDrawingEngine::GetDrawablesKeys(
    const FigureDrawingEngine::Drawables &drawables) {
  std::vector<std::string> keys;
  for (auto &[key, _] : drawables) {
    keys.push_back(key);
  }
  return keys;
}