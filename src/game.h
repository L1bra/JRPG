#ifndef GAME_H_
#define GAME_H_

#include "states.h"


class Game
{
private:
    void input();
    void update(float dt);
    void draw();

    void free_states();
public:
    Game();
    ~Game();

    void start();
private:
    sf::RenderWindow m_Window;
    std::vector<sf::VideoMode> vms;

    MainMenuState* menu_state;
    WorldMapState* world_state;
    LocalMapState* local_state;
    BattleState* battle_state;
};

#endif  // GAME_H_