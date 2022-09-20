#pragma once

#include "window.h"
#include "world_map_state.h"


class Game
{
private:
    Window* m_window;
    WorldMapState* m_world_state;
    Player* m_player;

    // Statistic stuff  
    sf::Font m_statistic_font;
    sf::Text m_statistic_text;
    sf::Time m_statistic_update_time;
    std::size_t m_statistic_num_frames;

    static const sf::Time time_per_frame;
private:
    void input();
    void update(sf::Time et);
    void draw();

    void update_statistic(sf::Time et);
    bool is_running() const;
public:
    Game();
    ~Game();

    bool init();
    void start();
};