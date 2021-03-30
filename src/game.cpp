#include "game.h"


Game::Game()
    :
    menu_state(new MainMenuState()),
    world_state(new WorldMapState()),
    local_state(new LocalMapState()),
    battle_state(new BattleState()),
    vms(sf::VideoMode::getFullscreenModes())
{    
    m_Window.create(vms.at(0), "Title", sf::Style::Fullscreen);
}

Game::~Game()
{
    free_states();
}

void Game::free_states()
{
    delete menu_state;
    delete world_state;
    delete local_state;
    delete battle_state;
}

void Game::start()
{
    sf::Clock clock;

    gameMode().Add("mainmenu", menu_state);
    gameMode().Add("worldmap", world_state);
    gameMode().Add("localmap", local_state);
    gameMode().Add("battle", battle_state);
    
    gameMode().Push("mainmenu");

    while(m_Window.isOpen())
    {
        sf::Event event;
        while(m_Window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                {
                    m_Window.close();
                } break;

                case sf::Event::KeyPressed: //  Main menu and parts where single input required
                {
                    gameMode().Input(event.key.code);
                } break;

                default: break;
            }
        }

        sf::Time dt = clock.restart();
        float dt_sec = dt.asSeconds();

        input();
        update(dt_sec);
        draw();
    }
}


void Game::input()
{
    gameMode().Input(sf::Keyboard::Unknown); // idk what im doing
}


void Game::update(float dt)
{
    gameMode().Update(dt);
}


void Game::draw()
{   
    m_Window.clear(sf::Color::White);
    gameMode().Render(m_Window);
    m_Window.display();
}