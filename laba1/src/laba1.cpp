#include "../include/laba1.h"

#include <SFML/Graphics.hpp>

#include <array>
#include <cmath>

namespace {
float degreeToRad(float angle) {
  const float pi = 4.f * std::atan(1);
  return angle * (pi) / 180;
}

float getLength(const Vector2& vec) {
  return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

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
}  // namespace

bool isTranslationKey(const sf::Keyboard::Key& key) {
  return key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Down ||
         key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::Right;
}

Rectangle::Rectangle(const Vector2& point, float length, float height)
    : color(sf::Color::Blue) {
  points[0] = point;
  points[1] = {point.x, point.y - height};
  points[2] = {point.x + length, point.y - height};
  points[3] = {point.x + length, point.y};
}

sf::ConvexShape Rectangle::getShape() {
  sf::ConvexShape convex;
  convex.setPointCount(points.size());
  for (int i = 0; i < points.size(); ++i)
    convex.setPoint(i, points[i]);
  convex.setFillColor(color);
  return convex;
}

Vector2 Rectangle::getMiddlePoint() {
  return {(points[0].x + points[2].x) / 2, (points[0].y + points[2].y) / 2};
}

void Rectangle::setFillColor(const sf::Color& i_color) {
  color = i_color;
}

void Rectangle::apply(const Matrix3& matrix) {
  for (auto& point : points)
    point = matrix.transformPoint(point);
}

RectanglePosHolder::RectanglePosHolder(Rectangle& i_rectangle)
    : rectangle(i_rectangle), startPos(i_rectangle.getMiddlePoint()) {
  rectangle.apply(getTranslationMatrix(-startPos.x, -startPos.y));
}

RectanglePosHolder::~RectanglePosHolder() {
  rectangle.apply(getTranslationMatrix(startPos.x, startPos.y));
}

void translate(Rectangle& rectangle, const sf::Keyboard::Key& key) {
  switch (key) {
    case sf::Keyboard::Key::Up:
      rectangle.apply(getTranslationMatrix(0, -moveDistance));
      break;

    case sf::Keyboard::Key::Down:
      rectangle.apply(getTranslationMatrix(0, moveDistance));
      break;

    case sf::Keyboard::Key::Left:
      rectangle.apply(getTranslationMatrix(-moveDistance, 0));
      break;

    case sf::Keyboard::Key::Right:
      rectangle.apply(getTranslationMatrix(moveDistance, 0));
      break;

    default:
      break;
  }
}

void scale(Rectangle& rectangle, float delta) {
  RectanglePosHolder holder(rectangle);
  const float scaleKoef = delta > 0 ? scaleIncr : scaleDecr;
  const Matrix3 scalingMatrix = getScalingMatrix(scaleKoef, scaleKoef);
  rectangle.apply(scalingMatrix);
}

void rotate(Rectangle& rectangle, const sf::Mouse::Button& button) {
  RectanglePosHolder holder(rectangle);
  const float angle =
      button == sf::Mouse::Button::Left ? rotationAngle : -rotationAngle;

  const Matrix3 rotationMatrix = getRotationMatrix(degreeToRad(angle));
  rectangle.apply(rotationMatrix);
}
