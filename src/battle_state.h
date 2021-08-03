#ifndef BATTLE_STATE_H_
#define BATTLE_STATE_H_

#include "state_machine.h"
#include "entity.h"
#include "action.h"
#include "queue.h"
#include "gui.h"
#include "gfx.h"

#include <array>


enum class Entity_battle_state : uint8_t
{
    WAIT = 0,
    COMMAND,
    ACTION
};


class BattleState : public State
{
private:
    // const
    enum 
    { 
        PLAYER_INDEX = 0,
        ENEMY_OFFSET = 3,
        MAX_ENTITY_INDEX = 5,
        MAX_ENTITY = 6
    };

    sf::Vector2f BLUE_SPAWN_POSITION;
    sf::Vector2f RED_SPAWN_POSITION;
    sf::Vector2f YELLOW_SPAWN_POSITION;

    // other
    std::shared_ptr<sf::Texture> m_BattleTexture;
    sf::Sprite m_BattleSprite;
    
    StateMachine* battleMode;
    GFX* gfx_data;
    sf::VideoMode& vm;
    
    // std::array<Entity, MAX_ENTITY> entities;
    std::vector<Action*> m_Actions;
    
    // cds::Queue<Entity> queue;

private:
    void init_party_entities();
    void init_enemy_entities();

    void battle_init();
    void free_stuff();

    // static bool sort_by_time(State& a, State& b);
public:
    BattleState(GFX* gfx);
    ~BattleState();

    void Input() override;
    void Update(float elapsedTime) override;
    void Render(Window& window) override;
    void OnEnter() override;
    void OnExit() override;
};

#endif  // BATTLE_STATE_H_