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
    
    std::array<Entity, MAX_ENTITY> entities;
    std::vector<Action*> m_Actions;
    
    ds::Queue<Entity> queue;

    GFX* gfx_data;
    sf::VideoMode& vm;
    StateMachine* battleMode;
private:
    void init_party_entities();
    void init_enemy_entities();

    void battle_init();
    void free_stuff();

    // static bool sort_by_time(State& a, State& b);
public:
    BattleState(GFX* gfx);
    ~BattleState();

    void Input(sf::Keyboard::Key key_code) override;
    void Update(float elapsedTime) override;
    void Render(sf::RenderWindow& window) override;
    void OnEnter() override;
    void OnExit() override;
};


class BattleTick : public State
{
private:
    Action* top_action;
    std::vector<Action*> battle_actions;
    StateMachine* battleMode;
public:
    BattleTick(StateMachine* battleMode, std::vector<Action*> battle_actions);
    ~BattleTick();

    void Input(sf::Keyboard::Key key_code) override;
    void Update(float elapsedTime) override;
    void Render(sf::RenderWindow& window) override;
    void OnEnter() override;
    void OnExit() override;
};


class BattleExecute : public State
{
public:
    BattleExecute(StateMachine* battleMode, std::vector<Action*> battle_actions);
    ~BattleExecute();

    void Input(sf::Keyboard::Key key_code) override;
    void Update(float elapsedTime) override;
    void Render(sf::RenderWindow& window) override;
    void OnEnter() override;
    void OnExit() override;
private:
    //
};


class BattleMenuState : public State
{
private:
    //
public:
    BattleMenuState();
    ~BattleMenuState();

    void Input(sf::Keyboard::Key key_code) override;
    void Update(float elapsedTime) override;
    void Render(sf::RenderWindow& window) override;
    void OnEnter() override;
    void OnExit() override;
};


class BattleAnimationState : public State
{
private:
    //
public:
    BattleAnimationState();
    ~BattleAnimationState();

    void Input(sf::Keyboard::Key key_code) override;
    void Update(float elapsedTime) override;
    void Render(sf::RenderWindow& window) override;
    void OnEnter() override;
    void OnExit() override;
};

#endif  // BATTLE_STATE_H_