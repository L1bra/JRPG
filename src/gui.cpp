#include "gui.h"

// TODO: rename variables
gui::Button::Button(float x, float y, float width, float height,
    sf::Font font, std::string str, unsigned character_size,
    sf::Color text_idle_color, sf::Color text_hover_color,
    sf::Color text_active_color, sf::Color idle_color,
    sf::Color hover_color, sf::Color active_color,
    sf::Color outline_idle_color,
    sf::Color outline_hover_color,
    sf::Color outline_active_color,
    short unsigned id
)
    :
    x(x),
    y(y),
    width(width),
    height(height),
    id(id),
    button_pos(this->width, this->height),
    button_state(BTN_IDLE),
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
    this->text.setFont(this->font);
    this->text.setString(str);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        shape.getPosition().y
    );
}

gui::Button::~Button() {}

bool gui::Button::is_pressed() const
{
    if (button_state == BTN_ACTIVE)
        return true;
    return false;
}

// TODO: return local variable
const std::string& gui::Button::get_text() const
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

sf::Vector2f gui::Button::get_pos() const
{
    return this->shape.getPosition();
}

BTN_STATE gui::Button::get_state() const
{
    return button_state;
}

void gui::Button::update(const sf::Vector2f& cursor_pos)
{
    //input.update();
    button_state = BTN_IDLE;

    if (cursor_pos == this->shape.getPosition())
    {
        button_state = BTN_HOVER;

        // pressed
        // replace with new input system
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            button_state = BTN_ACTIVE;
        }
    }

    switch (button_state)
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

void gui::Button::render(Window& window)
{
    window.draw(shape);
    window.draw(text);
}