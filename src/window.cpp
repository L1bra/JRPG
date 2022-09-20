#include "window.h"


Window::Window()
    :
    gfx(new GFX())
{
    if(gfx->load("cfg/gfx.ini"))
    {
        m_window = new sf::RenderWindow(gfx->resolution, gfx->title, (gfx->fullscreen ? sf::Style::Fullscreen : sf::Style::Default));
        m_window->setFramerateLimit(gfx->framerate);
        m_window->setVerticalSyncEnabled(gfx->vsync);
    }
    else
    {
        m_window = new sf::RenderWindow({800, 600}, "title", sf::Style::Default);
        m_window->setFramerateLimit(1);
        m_window->setVerticalSyncEnabled(true);
    }
}

Window::~Window()
{
    delete gfx;
    delete m_window;
}

void Window::update()
{
}

void Window::begin_draw(const sf::Color& color)
{
    m_window->clear(color);
}

void Window::draw(const sf::Drawable& drawable) const
{
    m_window->draw(drawable);
}

void Window::draw(const sf::VertexArray vao, const sf::RenderStates states) const
{
    m_window->draw(vao, states);
}

void Window::end_draw()
{
    m_window->display();
}

void Window::set_view(const sf::View& view) const
{
    m_window->setView(view);
}

const sf::View& Window::get_view() const
{
    return m_window->getView();
}

const sf::View& Window::get_default_view() const
{
    return m_window->getDefaultView();
}

GFX& Window::get_gfx() const
{
    return *gfx;
}

sf::RenderWindow& Window::get_render_window() const
{
    return *m_window;
}

bool Window::poll_event(sf::Event& event)
{
    return m_window->pollEvent(event);
}

bool Window::is_open() const
{
    return m_window->isOpen();
}

void Window::close()
{
    m_window->close();
}