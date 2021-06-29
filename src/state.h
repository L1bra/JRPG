#ifndef STATE_H_
#define STATE_H_

#include <SFML/Graphics.hpp>


class State
{
public:
    virtual ~State() {};

    virtual void Input() = 0;
    virtual void Update(float elapsedTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
};


#endif  // STATE_H_