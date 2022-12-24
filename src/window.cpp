#include "window.h"


Window::Window()
    :
    m_gfx(new GFX())
{
    if(m_gfx->load("cfg/gfx.ini"))
    {
        m_window = new sf::RenderWindow(m_gfx->resolution, m_gfx->title, (m_gfx->fullscreen ? sf::Style::Fullscreen : sf::Style::Default));
        m_window->setFramerateLimit(m_gfx->framerate);
        m_window->setVerticalSyncEnabled(m_gfx->vsync);
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
    delete m_gfx;
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

void Window::resize_view()
{
    float ap = float(this->get_render_window().getSize().x) / float(this->get_render_window().getSize().y);
    auto view = this->get_view();
    view.setSize(m_gfx->resolution.width * ap, m_gfx->resolution.height);
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
    return *m_gfx;
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