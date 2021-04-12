#ifndef GUI_H_
#define GUI_H_

#include <SFML/Graphics.hpp>
#include <cmath>

typedef enum
{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
} BTN_STATE;

namespace gui
{

    const float p2pX(const float p, const sf::VideoMode& vm);
    const float p2pY(const float p, const sf::VideoMode& vm);
    const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);
    
    class Button
    {
    private:
        float x;
        float y;

        float width;
        float height;
        
        sf::Vector2f button_pos;
        BTN_STATE button_state;
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
                sf::Font font, std::string str, unsigned character_size,
                sf::Color text_idle_color = sf::Color(200, 200, 200, 200),
                sf::Color text_hover_color = sf::Color(255, 255, 255, 255),
                sf::Color text_active_color = sf::Color(20, 20, 20, 50), 
                sf::Color idle_color = sf::Color(70, 70, 70, 0), 
                sf::Color hover_color = sf::Color(150, 150, 150, 0), 
                sf::Color active_color = sf::Color(20, 20, 20, 0),
                sf::Color outline_idle_color = sf::Color::Transparent,
                sf::Color outline_hover_color = sf::Color::Transparent,
                sf::Color outline_active_color = sf::Color::Transparent,
                short unsigned id = 0
                );
        ~Button();

        const bool is_pressed() const;

        const std::string get_text() const;
        const short unsigned& get_id() const;
        sf::Vector2f get_pos() const;
        BTN_STATE get_state() const;

        void set_text(const std::string text);
        void set_id(const short unsigned id);


        void update(const sf::Vector2f& cursor_pos);   // const sf::Vector2i& mouse_pos_window;
        void render(sf::RenderTarget& target);
    };
}

#endif  // GUI_H_