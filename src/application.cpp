#include "application.h"

const sf::Time Application::time_per_frame = sf::seconds(1.f / 60.f);

Application::Application()
    :
    m_window(),
    m_player(),
    m_textures(),
    m_fonts(),
    m_state_stack(State::Context(m_window, m_textures, m_fonts, m_player)),
    m_statistic_font(),
    m_statistic_text(),
    m_statistic_update_time(),
    m_statistic_num_frames(0)
{
    m_window.get_render_window().setKeyRepeatEnabled(false);

    m_fonts.load(Fonts::Main, "res/fonts/PixellettersFull.ttf");
    m_textures.load(Textures::TitleScreen, "res/background/title_screen.png");

    m_statistic_text.setFont(m_fonts.get(Fonts::Main));
    m_statistic_text.setPosition(5.f, 5.f);
    m_statistic_text.setCharacterSize(50);

    this->register_states();
    m_state_stack.push_state(States::Title);
}

Application::~Application()
{
}

bool Application::init()
{
    return true;
}

void Application::start()
{
    // TODO: 
    // we assume that window->setFrameLimit() is already set
    sf::Clock clock;
    sf::Time last_time = sf::Time::Zero;
    while(this->is_running())
    {
        sf::Time elapsed_time = clock.restart();
        last_time += elapsed_time;
        while(last_time > time_per_frame)
        {
            last_time -= time_per_frame;

            input();
            update(time_per_frame);

            if (m_state_stack.is_empty()) m_window.close();
        } 

        update_statistic(elapsed_time);
        draw();
    }
}

void Application::input()
{
    sf::Event event;
    while(m_window.poll_event(event))
    {
        m_state_stack.handle_event(event);
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                m_window.close();
            } break;
        }
    }
}

void Application::update(sf::Time dt)
{
    m_state_stack.update(dt);
}

void Application::draw()
{
    m_window.begin_draw(sf::Color::White);

    m_state_stack.draw();

    m_window.set_view(m_window.get_default_view());
    m_window.draw(m_statistic_text);
    m_window.end_draw();
}

void Application::update_statistic(sf::Time et)
{
    m_statistic_update_time += et;
    m_statistic_num_frames += 1;

    if (m_statistic_update_time >= sf::seconds(1.0f))
    {
        m_statistic_text.setString("FPS: " + to_string(m_statistic_num_frames));
        m_statistic_update_time -= sf::seconds(1.0f);
        m_statistic_num_frames = 0;
    }
}

void Application::register_states()
{
    m_state_stack.register_state<TitleState>(States::Title);
    m_state_stack.register_state<MenuState>(States::Menu);
    m_state_stack.register_state<SettingsState>(States::Settings);
    m_state_stack.register_state<GameState>(States::Game);
    m_state_stack.register_state<PauseState>(States::Pause);
}

bool Application::is_running() const
{
    return m_window.is_open();
}