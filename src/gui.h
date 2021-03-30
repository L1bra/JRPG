#ifndef GUI_H_
#define GUI_H_

#include <SFML/Graphics.hpp>
#include <cmath>

enum button_state
{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

namespace gui
{
    const float p2pX(const float p, const sf::VideoMode& vm);
    const float p2pY(const float p, const sf::VideoMode& vm);
    const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);
    
    class Button
    {
    private:
        short unsigned button_state;
        short unsigned id;

        sf::RectangleShape shape;
        sf::Font font;
        sf::Text text;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Color outlineIdleColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;
    public:
        Button(float x, float y, float width, float height,
                sf::Font font, std::string text, unsigned character_size,
                sf::Color text_idle_color, sf::Color text_hover_color, 
                sf::Color text_active_color, sf::Color idle_color, 
                sf::Color hover_color, sf::Color active_color,
                sf::Color outline_idle_color = sf::Color::Transparent,
                sf::Color outline_hover_color = sf::Color::Transparent,
                sf::Color outline_active_color = sf::Color::Transparent,
                short unsigned id = 0
                );
        ~Button();

        const bool is_pressed() const;
        const std::string get_text() const;
        const short unsigned& get_id() const;

        void set_text(const std::string text);
        void set_id(const short unsigned id);

        void update(sf::Vector2f cursor_pos);   // const sf::Vector2i& mouse_pos_window;
        void render(sf::RenderTarget& target);
    };
}

#endif  // GUI_H_