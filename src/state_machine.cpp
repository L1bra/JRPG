#include "state_machine.h"
#include <iostream>

EmptyState::EmptyState() {}
EmptyState::~EmptyState() {}
void EmptyState::Input(sf::Keyboard::Key key_code) {}
void EmptyState::Update(float elapsedTime) {}
void EmptyState::Render(sf::RenderWindow& window) {}
void EmptyState::OnEnter() {}
void EmptyState::OnExit() {}


StateMachine::StateMachine()
    :
    state(new EmptyState()),
    top(new EmptyState())
{
}

// TODO: 
StateMachine::~StateMachine() 
{
}

void StateMachine::Input(sf::Keyboard::Key key_code)
{
    if(m_Stack.size())
    {
        top = m_Stack.back();
        top->Input(key_code);
    }
}

void StateMachine::Update(float elapsedTime)
{
    if(m_Stack.size())
    {
        top = m_Stack.back();
        top->Update(elapsedTime);
    }
}

void StateMachine::Render(sf::RenderWindow& window)
{
    if(m_Stack.size())
    {
        top = m_Stack.back();
        top->Render(window);
    }
}

void StateMachine::Push(const std::string& name)
{
    state->OnExit();
    state = m_States[name];

    m_Stack.push_back(state);
    // TODO: logger
    std::cout << name << " pushed to stack." << std::endl;
    state->OnEnter();
}

void StateMachine::Add(std::string name, State* state)
{
    m_States[name] = state;
}

void StateMachine::Pop()
{
    m_Stack.pop_back();
}

bool StateMachine::isEmpty()
{
    return m_Stack.size() ? 1 : 0;
}

std::size_t StateMachine::size()
{
    return m_Stack.size();
}

StateMachine& gameMode()
{
    static StateMachine ss;
    return ss;
}