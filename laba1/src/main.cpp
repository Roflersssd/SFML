#include "../include/laba1.h"

#include <SFML/Graphics.hpp>

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