#include "easy-gui.h"

// It is a demonstration.
int main() {
  sf::RenderWindow window(sf::VideoMode(600, 600), "Easy GUI demo");

  Window::set_icon(window, "resources/icon.png");

  window.setFramerateLimit(60);

  sf::Font font = Helper::load_font("resources/roboto.ttf");

  int counter = 0;

  Window::Text counter_label(
    (std::string) "Counter: " += std::to_string(counter),
    { 300.0f, 30.0f },
    font,
    sf::Color::Green
  );

  Window::Text button_label(
    "Increase the counter",
    { 300.0f, 70.0f },
    font,
    sf::Color::Magenta
  );

  Window::RectButton button(
    button_label,
    { 300.0f, 50.0f },
    { 300.0f, 70.0f }
  );

  /* Main loop or game loop
    1. Handles events
    2. Updates states
    3. Draws/renders everything
  */
  while (window.isOpen()) {
    /* EVENT HANDLING
      I highly recommend you to write a separated
      event handler, like a void function in other file.
    */
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      button.get_button_status(window, event);

      if (button.is_pressed) {
        counter += 1;
      }

      if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Num1) {
          counter_label.update(sf::Color::Red);
        }
      }
    }

    /* UPDATING STATES */
    counter_label.update((std::string)"Counter: " += std::to_string(counter));

    /* DRAWING THINGS */
    // If your background is just a solid color, then put it here
    window.clear(sf::Color::White); 

    counter_label.draw(window);

    button.draw(window);

    window.display();
  }

  return 0;
}
