#include "window.h"


Window::Window()
    :
    gfx(new GFX())
{
    // TODO: if load is failed
    gfx->load("src/cfg/gfx.init");

    if(gfx->fullscreen)
        window = new sf::RenderWindow(gfx->resolution, gfx->title, sf::Style::Fullscreen);
    else
        window = new sf::RenderWindow(gfx->resolution, gfx->title, sf::Style::Default);

    window->setFramerateLimit(gfx->framerate);
    window->setVerticalSyncEnabled(gfx->vsync);
}

Window::~Window()
{
    delete gfx;
    delete window;
}

void Window::update()
{
    sf::Event event;
    if(window->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                window->close();
            } break;
        }
    }
}

void Window::begin_draw(const sf::Color& color)
{
    window->clear(color);
}

void Window::draw(const sf::Drawable& drawable)
{
    window->draw(drawable);
}

void Window::end_draw()
{
    window->display();
}

bool Window::is_open() const
{
    return window->isOpen();
}