#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

class tPoint {
    public:
    tPoint(sf::RenderWindow& window) :
      window_where_draw_(window) {
        setPosition(0, 0);
        setColor(50,50,50);
    }
    tPoint(float x, float y, sf::RenderWindow& window)
    : shape_(sf::CircleShape(1.0f)),
      window_where_draw_(window) {
        setPosition(x, y);
        setColor(50,50,50);
    }
    void Draw() {
        window_where_draw_.draw(shape_);
    }
    void setPosition(float x, float y) {
        shape_.setPosition({x, y});
    }
    std::pair<float, float> getPosition() const{
        return {shape_.getPosition().x, shape_.getPosition().y};
    }
    void setColor(uint8_t r, uint8_t g, uint8_t b) {
        shape_.setFillColor(sf::Color(r, g, b));
    }
    std::tuple<uint8_t, uint8_t, uint8_t> getRGBColor() const{
        return {shape_.getFillColor().r, shape_.getFillColor().g, shape_.getFillColor().b};
    }
    void setSize(float radius) {
        shape_.setRadius(radius);
    }
    float getSize() const {
        return shape_.getRadius();
    }
    void movePointBy(float delta_x, float delta_y) {
        auto [x, y] = getPosition();
        setPosition(x + delta_x, y + delta_y);
    }
    private:
    sf::CircleShape shape_;
    sf::RenderWindow& window_where_draw_;
};



int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    std::vector<tPoint> points;
    for (int i = 0; i < 100; ++i) {
        tPoint point(fmodf(rand(), window.getSize().x),
                     fmodf(rand(), window.getSize().y),
                     window);
        point.setColor(rand()% 255, rand()% 255, rand()% 255);
        points.push_back(std::move(point));
    }
    tPoint main_point(window);
    main_point.setPosition(500, 500);
    main_point.setColor(100, 100, 100);
    main_point.setSize(50);
    while (window.isOpen())
    {   
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left){
                    main_point.movePointBy(-10, 0);
                }
                else if (event.key.code == sf::Keyboard::Right){
                    main_point.movePointBy(10, 0);
                }
                if (event.key.code == sf::Keyboard::Up){
                    main_point.movePointBy(0, -10);
                }
                else if (event.key.code == sf::Keyboard::Down){
                    main_point.movePointBy(0, +10);
                }
            }
        }
        window.clear();
        for (auto& point : points) {
            point.Draw();
        }
        main_point.Draw();
        window.display();
    }
}