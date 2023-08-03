#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <cmath>

namespace Helper {
  /// @brief Loads an image.
  /// @param image_path - The path where the image is located.
  /// @returns An icon image.
  sf::Image load_image(const sf::String& image_path) {
    sf::Image image;

    if (!image.loadFromFile(image_path)) {
      throw std::runtime_error("The image could not be loaded. Verify if the image path is correct.");
    }

    return image;
  }

  /// @brief Loads an font.
  /// @param font_path - The path where the font is located.
  /// @returns A font.
  sf::Font load_font(const sf::String& font_path) {
    sf::Font font;

    if (!font.loadFromFile(font_path)) {
      throw std::runtime_error("The font could not be loaded. Check if the font is correctly at where you pointed.");
    }

    return font;
  }

  // Rounds a float vector
  sf::Vector2f round(const sf::Vector2f vector) {
    return sf::Vector2f(std::round(vector.x), std::round(vector.y));
  }

  // Returns the center of something that has bounds. Useful when centering the origin position.
  sf::Vector2f get_center(sf::FloatRect global_bounds, sf::FloatRect local_bounds) {
    sf::Vector2f center(
      global_bounds.width / 2.0f,
      global_bounds.height / 2.0f
    );
    sf::Vector2f centered_local_bounds(
      center.x + local_bounds.left,
      center.y + local_bounds.top
    );

    return Helper::round(centered_local_bounds);
  }
}

namespace Window {
  /// @brief Loads and sets an icon.
  /// @param window - The main window.
  /// @param icon_path - The path where the icon is located.
  void set_icon(sf::RenderWindow& window, const sf::String& icon_path) {
    sf::Image icon = Helper::load_image(icon_path);

    window.setIcon(
      icon.getSize().x,
      icon.getSize().y,
      icon.getPixelsPtr()
    );
  }

  /// @brief A centered text component.
  class Text {
  private:
    sf::Text m_text;
  public:
    /// @brief Creates a text component.
    /// @param text - The text to be displayed.
    /// @param position - The position where it will be displayed.
    /// @param font - The font it needs to be rendered.
    /// @param color - The color to render the text.
    /// @param style - The style of the text. Bold, italic, strike through, etc.
    /// @param character_size - The font size.
    Text(
      const sf::String& text,
      sf::Vector2f position,
      sf::Font& font,
      const sf::Color& color,
      sf::Uint32 style = sf::Text::Regular,
      unsigned int character_size = 30
    ) {
      m_text = sf::Text(text, font, character_size);

      m_text.setOrigin(Helper::get_center(
        m_text.getGlobalBounds(),
        m_text.getLocalBounds()
      ));
      m_text.setPosition(position);
      m_text.setFillColor(color);
      m_text.setStyle(style);
    }

    // Returns the text component.
    sf::Text get() {
      return m_text;
    }

    // Changes the text to a new one.
    void update(const sf::String& text) {
      m_text.setString(text);
    }

    // Changes the position of the text to a new one.
    void update(sf::Vector2f& position) {
      m_text.setPosition(position);
    }

    // Changes the color of the text to a new one.
    void update(const sf::Color& color) {
      m_text.setFillColor(color);
    }

    // Draws the component on the screen.
    void draw(sf::RenderWindow& window) {
      window.draw(m_text);
    }
  };
}
