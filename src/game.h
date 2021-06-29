#ifndef GAME_H_
#define GAME_H_

#include "states.h"
#include "gfx.h"


class Game
{
private:
    void input();
    void update(float dt);
    void draw();

    void init_settings();

    void free_states();
public:
    Game();
    ~Game();

    void start();
private:
    sf::RenderWindow* m_Window;
    GFX* gfx;

    MainMenuState* menu_state;
    WorldMapState* world_state;
    LocalMapState* local_state;
    BattleState* battle_state;
};

#endif  // GAME_H_