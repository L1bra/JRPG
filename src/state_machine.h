#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "resource_manager.h"

#include <map>

#include <SFML/Graphics.hpp>

class Action;

class State
{
public:
    virtual ~State() {};

    virtual void Input(sf::Keyboard::Key key_code) = 0;
    virtual void Update(float elapsedTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
};


class EmptyState : public State
{
public:
    EmptyState();
    ~EmptyState();

    void Input(sf::Keyboard::Key key_code) override;
    void Update(float elapsedTime) override;
    void Render(sf::RenderWindow& window) override;
    void OnEnter() override;
    void OnExit() override;
};

class StateMachine final
{
private:
    std::map<std::string, State*> m_States;
    std::vector<State*> m_Stack;
    State* state;
    State* top;
private:
    void sm_free();
public:
    StateMachine();
    ~StateMachine();

    void Input(sf::Keyboard::Key key_code);
    void Update(float elapsedTime);
    void Render(sf::RenderWindow& window);

    void Add(std::string, State* state);
    void Push(const std::string& name);
    void Pop();

    bool isEmpty();
    std::size_t size();
};


StateMachine& gameMode();

#endif  // STATE_MACHINE_H_