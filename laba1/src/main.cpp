#include <SFML/Graphics.hpp>

#include <array>
#include <cmath>
#include <iostream>

using Matrix3 = sf::Transform;
using Vector2 = sf::Vector2f;

constexpr float moveDistance = 1;
constexpr float scaleIncr = 1.001;
constexpr float scaleDecr = 0.999;
constexpr float rotationAngle = 0.1;

float degreeToRad(float angle) {
  const float pi = 4.f * std::atan(1);
  return angle * (pi) / 180;
}

float getLength(const Vector2& vec) {
  return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

class Rectangle {
 public:
  Rectangle(const Vector2& point, float length, float height)
      : color(sf::Color::Blue) {
    points[0] = point;
    points[1] = {point.x, point.y - height};
    points[2] = {point.x + length, point.y - height};
    points[3] = {point.x + length, point.y};
  }

  sf::ConvexShape getShape() {
    sf::ConvexShape convex;
    convex.setPointCount(points.size());
    for (int i = 0; i < points.size(); ++i)
      convex.setPoint(i, points[i]);
    convex.setFillColor(color);
    return convex;
  }

  Vector2 getMiddlePoint() {
    return {(points[0].x + points[2].x) / 2, (points[0].y + points[2].y) / 2};
  }

  void setFillColor(const sf::Color& i_color) { color = i_color; }

  void apply(const Matrix3& matrix) {
    for (auto& point : points)
      point = matrix.transformPoint(point);
  }

 private:
  std::array<Vector2, 4> points;
  sf::Color color;
};

Matrix3 getTranslationMatrix(float dx, float dy) {
  return {1.f, 0.f, dx, 0.f, 1.f, dy, 0.f, 0.f, 1.f};
}

Matrix3 getRotationMatrix(float fi) {
  return {std::cos(fi), -std::sin(fi), 0.f, std::sin(fi), std::cos(fi),
          0.f,          0.f,           0.f, 1.f};
}

Matrix3 getScalingMatrix(float da, float db) {
  return {da, 0.f, 0.f, 0.f, db, 0.f, 0.f, 0.f, 1.f};
}

bool isTranslationKey(const sf::Keyboard::Key& key) {
  return key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Down ||
         key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::Right;
}

void translate(Rectangle& shape, const sf::Keyboard::Key& key) {
  switch (key) {
    case sf::Keyboard::Key::Up:
      shape.apply(getTranslationMatrix(0, -moveDistance));
      break;

    case sf::Keyboard::Key::Down:
      shape.apply(getTranslationMatrix(0, moveDistance));
      break;

    case sf::Keyboard::Key::Left:
      shape.apply(getTranslationMatrix(-moveDistance, 0));
      break;

    case sf::Keyboard::Key::Right:
      shape.apply(getTranslationMatrix(moveDistance, 0));
      break;

    default:
      break;
  }
}

void scale(Rectangle& shape, float delta) {
  const Vector2 middlePoint = shape.getMiddlePoint();
  shape.apply(getTranslationMatrix(-middlePoint.x, -middlePoint.y));

  const Matrix3 scalingMatrix = delta > 0
                                    ? getScalingMatrix(scaleIncr, scaleIncr)
                                    : getScalingMatrix(scaleDecr, scaleDecr);
  shape.apply(scalingMatrix);

  shape.apply(getTranslationMatrix(middlePoint.x, middlePoint.y));
}

void rotate(Rectangle& shape, const sf::Mouse::Button& button) {
  const Vector2 middlePoint = shape.getMiddlePoint();
  shape.apply(getTranslationMatrix(-middlePoint.x, -middlePoint.y));

  const float angle =
      button == sf::Mouse::Button::Left ? rotationAngle : -rotationAngle;
  const Matrix3 rotationMatrix = getRotationMatrix(degreeToRad(angle));
  shape.apply(rotationMatrix);

  shape.apply(getTranslationMatrix(middlePoint.x, middlePoint.y));
}

void processEvent(Rectangle& rectangle, const sf::Event& event) {
  switch (event.type) {
    case sf::Event::KeyPressed:
      if (isTranslationKey(event.key.code))
        translate(rectangle, event.key.code);
      break;

    case sf::Event::MouseWheelScrolled:
      scale(rectangle, event.mouseWheelScroll.delta);
      break;

    case sf::Event::MouseButtonPressed:
      rotate(rectangle, event.mouseButton.button);
      break;

    default:
      break;
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Laba1");
  Rectangle rectangle({200, 200}, 100, 50);
  rectangle.setFillColor(sf::Color::Green);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    processEvent(rectangle, event);

    window.clear();
    window.draw(rectangle.getShape());
    window.display();
  }

  return 0;
}