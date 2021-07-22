#ifndef WINDOW_H_
#define WINDOW_H_

#include "gfx.h"

#include <SFML/Graphics.hpp>

class Window
{
private:
    sf::RenderWindow* window;
    GFX* gfx;
public:
    Window();
    ~Window();
    
    void update();

    void begin_draw(const sf::Color& color);
    void draw(const sf::Drawable& drawable);
    void end_draw();

    bool is_open() const;
};

#endif  // WINDOW_H_