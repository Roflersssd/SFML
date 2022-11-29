#pragma once

#include <SFML/Graphics.hpp>

#include <array>

using Matrix3 = sf::Transform;
using Vector2 = sf::Vector2f;

constexpr float moveDistance = 1;
constexpr float scaleIncr = 1.001;
constexpr float scaleDecr = 0.999;
constexpr float rotationAngle = 0.1;

class Rectangle {
 public:
  Rectangle(const Vector2& point, float length, float height);

  sf::ConvexShape getShape();

  Vector2 getMiddlePoint();

  void setFillColor(const sf::Color& i_color);

  void apply(const Matrix3& matrix);

 private:
  std::array<Vector2, 4> points;
  sf::Color color;
};

class RectanglePosHolder {
 public:
  RectanglePosHolder(Rectangle& i_rectangle);

  ~RectanglePosHolder();

 private:
  Rectangle& rectangle;
  Vector2 startPos;
};

bool isTranslationKey(const sf::Keyboard::Key& key);

void translate(Rectangle& rectangle, const sf::Keyboard::Key& key);

void scale(Rectangle& rectangle, float delta);

void rotate(Rectangle& rectangle, const sf::Mouse::Button& button);
