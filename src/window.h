#pragma once

#include "gfx.h"

#include <SFML/Graphics.hpp>

class Window
{
private:
    sf::RenderWindow* m_window;
    GFX* gfx;
public:
    Window();
    ~Window();
    
    void update();

    void begin_draw(const sf::Color& color);
    void draw(const sf::Drawable& drawable) const;
    void draw(const sf::VertexArray vao, const sf::RenderStates states) const;
    void end_draw();

    void set_view(const sf::View& view) const;
    const sf::View& get_view() const;
    const sf::View& get_default_view() const;
    GFX& get_gfx() const;

    sf::RenderWindow& get_render_window() const;
    bool poll_event(sf::Event& event);
    
    bool is_open() const;
    void close();

};