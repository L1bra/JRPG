#include "game.h"


Game::Game()
    :
    gfx(new GFX()),
    loading_state(new ScreenSplash(gfx)),
    menu_state(new MainMenuState(gfx)),
    world_state(new WorldMapState(gfx)),
    local_state(new LocalMapState(gfx)),
    battle_state(new BattleState(gfx))
{
}

Game::~Game()
{
    free_states();
    delete gfx;
}

void Game::free_states()
{
    delete menu_state;
    delete world_state;
    delete local_state;
    delete battle_state;
}

void Game::init()
{
    gameMode().Add("loading", loading_state);
    gameMode().Add("mainmenu", menu_state);
    gameMode().Add("worldmap", world_state);
    gameMode().Add("localmap", local_state);
    gameMode().Add("battle", battle_state);

    start();
}

void Game::start()
{
    sf::Clock clock;

    gameMode().Push("loading");

    while(is_running())
    {
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
    window.update();
    gameMode().Update(dt);
}

void Game::draw()
{
    // TODO: REMOVE
    window.begin_draw(sf::Color::White);
    gameMode().Render(window);
    window.end_draw();
}

bool Game::is_running() const
{
    return window.is_open();
}