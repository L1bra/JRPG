#include "game.h"

const sf::Time Game::time_per_frame = sf::seconds(1.f / 60.f);

Game::Game()
    :
    m_window(new Window()),
    m_world_state(new WorldMapState(*m_window)),
    m_player(new Player()),
    m_statistic_font(),
    m_statistic_text(),
    m_statistic_update_time(),
    m_statistic_num_frames(0)
{
    m_window->get_render_window().setKeyRepeatEnabled(false);

    m_statistic_font.loadFromFile("res/fonts/PixellettersFull.ttf");
    m_statistic_text.setFont(m_statistic_font);
    m_statistic_text.setFillColor(sf::Color::Black);
    m_statistic_text.setPosition(5.f, 5.f);
    m_statistic_text.setCharacterSize(50);
}

Game::~Game()
{
    delete m_player;
    delete m_world_state;
    delete m_window;

    //delete m_ldtk_project;
}

bool Game::init()
{
    return true;
}

void Game::start()
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
        } 

        update_statistic(elapsed_time);
        draw();
    }
}

void Game::input()
{
    CommandQueue& commands = m_world_state->get_command_queue();
    sf::Event event;
    while(m_window->poll_event(event))
    {
        m_player->handle_event(event, commands);

        switch (event.type)
        {
            case sf::Event::Closed:
            {
                m_window->close();
            } break;

            case sf::Event::Resized:
            {
                std::cout << "resized size: " << event.size.width
                    << "x" << event.size.height << "\n";
            } break;
        }

        m_player->handle_realtime_input(commands);
    }
}

// TODO: rewrite to sf::Time dt everywhere
void Game::update(sf::Time et)
{
    //m_window->update();
    m_world_state->update(et);
}

void Game::draw()
{
    m_window->begin_draw(sf::Color::White);
    m_world_state->draw();

    m_window->set_view(m_window->get_default_view());
    m_window->draw(m_statistic_text);
    m_window->end_draw();
}

void Game::update_statistic(sf::Time et)
{
    m_statistic_update_time += et;
    m_statistic_num_frames += 1;

    if (m_statistic_update_time >= sf::seconds(1.0f))
    {
        m_statistic_text.setString(
            "Frames / Second = " + std::to_string(m_statistic_num_frames) + "\n" +
            "Times / Update = " + std::to_string(m_statistic_update_time.asMicroseconds() / m_statistic_num_frames) + "us"
        );
        m_statistic_update_time -= sf::seconds(1.0f);
        m_statistic_num_frames = 0;
    }
}

bool Game::is_running() const
{
    return m_window->is_open();
}