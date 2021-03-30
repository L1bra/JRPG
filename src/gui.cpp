#include "gui.h"

const float gui::p2pX(const float p, const sf::VideoMode& vm)
{
    return std::floor(static_cast<float>(vm.width) * (p / 100.f));
}

const float gui::p2pY(const float p, const sf::VideoMode& vm)
{
    return std::floor(static_cast<float>(vm.width) * (p/ 100.f));
}

const unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
    return static_cast<unsigned>((vm.width + vm.height) / modifier);
}


gui::Button::Button(float x, float y, float width, float height,
                sf::Font font, std::string text, unsigned character_size,
                sf::Color text_idle_color, sf::Color text_hover_color, 
                sf::Color text_active_color, sf::Color idle_color, 
                sf::Color hover_color, sf::Color active_color,
                sf::Color outline_idle_color,
                sf::Color outline_hover_color,
                sf::Color outline_active_color,
                short unsigned id
                )
        :
        button_state(BTN_IDLE),
        id(id),
        font(font),
        textIdleColor(text_idle_color),
        textHoverColor(text_hover_color),
        textActiveColor(text_active_color),
        idleColor(idle_color),
        hoverColor(hover_color),
        activeColor(active_color),
        outlineIdleColor(outline_idle_color),
        outlineHoverColor(outline_hover_color),
        outlineActiveColor(outline_active_color)
{
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(idle_color);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(outline_idle_color);

    // TODO: rename text string
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        shape.getPosition().y
    );
}

gui::Button::~Button() {}

const bool gui::Button::is_pressed() const
{
    if(button_state == BTN_ACTIVE)
        return true;
    return false;
}

const std::string gui::Button::get_text() const
{
    return this->text.getString();
}

const short unsigned& gui::Button::get_id() const
{
    return id;
}

void gui::Button::set_text(const std::string text)
{
    this->text.setString(text);
}

void gui::Button::set_id(const short unsigned id)
{
    // TODO: rename this either
    this->id = id;
}

void gui::Button::update(const sf::Vector2f cursor_pos)  // const sf::Vector2i& mouse_pos_window
{
    button_state = BTN_IDLE;

    if(shape.getGlobalBounds().contains(cursor_pos))
    {
        button_state = BTN_HOVER;

        // pressed
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            button_state = BTN_ACTIVE;
        }

        switch(button_state)
        {
            case BTN_IDLE:
            {
                shape.setFillColor(idleColor);
                this->text.setFillColor(textIdleColor);
                shape.setOutlineColor(outlineIdleColor);
            } break;

            case BTN_HOVER:
            {
                shape.setFillColor(hoverColor);
                this->text.setFillColor(textHoverColor);
                shape.setOutlineColor(outlineHoverColor);
            } break;

            case BTN_ACTIVE:
            {
                shape.setFillColor(activeColor);
                this->text.setFillColor(textActiveColor);
                shape.setOutlineColor(outlineActiveColor);
            } break;

            default:
            {
                shape.setFillColor(sf::Color::Red);
                this->text.setFillColor(sf::Color::Green);
                shape.setOutlineColor(sf::Color::Blue);
            } break;
        }
    }
}

void gui::Button::render(sf::RenderTarget& window)
{
    window.draw(shape);
    window.draw(text);
}