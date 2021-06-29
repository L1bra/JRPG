#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "state.h"
#include "resource_manager.h"

#include <map>
#include <SFML/Graphics.hpp>


class EmptyState : public State
{
public:
    EmptyState();
    ~EmptyState();

    void Input() override;
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
public:
    StateMachine();
    ~StateMachine();

    void Input();
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