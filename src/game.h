#ifndef GAME_H_
#define GAME_H_

#include "window.h"
#include "states.h"
#include "gfx.h"


class Game
{
private:
    Window window;
    GFX* gfx;

    ScreenSplash* loading_state;
    MainMenuState* menu_state;
    WorldMapState* world_state;
    LocalMapState* local_state;
    BattleState* battle_state;
private:
    void input();
    void update(float dt);
    void draw();

    void start();
    bool is_running() const;

    void init_settings();
    void free_states();

public:
    Game();
    ~Game();

    void init();
};

#endif  // GAME_H_