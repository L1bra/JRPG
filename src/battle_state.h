#ifndef BATTLE_STATE_H_
#define BATTLE_STATE_H_

#include "state_machine.h"
#include "entity.h"
#include "action.h"

class BattleState : public State
{
private:
    void init_party_entities();
    void init_enemy_entities();

    static bool sort_by_time(State& a, State& b);
public:
    BattleState();
    ~BattleState();

    void Input(sf::Keyboard::Key key_code);
    void Update(float elapsedTime);
    void Render(sf::RenderWindow& window);
    void OnEnter();
    void OnExit();

    void action_tick();
    void action_execute();

    // remove
    void TimeRemaining();
    void Decide();
    bool isReady();
private:
    std::shared_ptr<sf::Texture> m_BattleTexture;
    sf::Sprite m_BattleSprite;
    
    Entity entities[MAX_ENTITIES];
    std::vector<State*> m_Actions;

    StateMachine* battleMode;
    State* battle_tick;
    State* battle_execute;
};


class BattleTick : public State
{
public:
    BattleTick(StateMachine* bm);
    ~BattleTick();

    void Input(sf::Keyboard::Key key_code);
    void Update(float elapsedTime);
    void Render(sf::RenderWindow& window);
    void OnEnter();
    void OnExit();

    // remove
    void TimeRemaining();
    void Decide();
    bool isReady();

private:
    std::shared_ptr<sf::Texture> m_ActionFrameTexture;
    sf::Sprite m_ActionFrameSprite;

    StateMachine* battleMode;
public:

private:
    // fields
};


class BattleExecute : public State
{
public:
    BattleExecute(StateMachine* bm);
    ~BattleExecute();

    void Input(sf::Keyboard::Key key_code);
    void Update(float elapsedTime);
    void Render(sf::RenderWindow& window);
    void OnEnter();
    void OnExit();

    // remove
    void TimeRemaining();
    void Decide();
    bool isReady();
private:
    StateMachine* battleMode;
};


#endif  // BATTLE_STATE_H_