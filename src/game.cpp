#include "game.h"


Game::Game()
    :
    gfx(new GFX()),
    menu_state(new MainMenuState(gfx)),
    world_state(new WorldMapState(gfx)),
    local_state(new LocalMapState(gfx)),
    battle_state(new BattleState(gfx))
{
    init_settings();

    if(gfx->fullscreen)
        m_Window = new sf::RenderWindow(gfx->resolution, gfx->title, sf::Style::Fullscreen);
    else
        m_Window = new sf::RenderWindow(gfx->resolution, gfx->title, sf::Style::Default);
    
    m_Window->setFramerateLimit(gfx->framerate);
    m_Window->setVerticalSyncEnabled(gfx->vsync);
}

Game::~Game()
{
    free_states();
    delete gfx;
    delete m_Window;
}

void Game::init_settings()
{
    gfx->load("src/cfg/gfx.ini");
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

    while(m_Window->isOpen())
    {
        sf::Event event;
        while(m_Window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                {
                    m_Window->close();
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
    gameMode().Input();
}

void Game::update(float dt)
{
    gameMode().Update(dt);
}

void Game::draw()
{   
    m_Window->clear(sf::Color::White);
    gameMode().Render(*m_Window);
    m_Window->display();
}