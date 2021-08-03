#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <SFML/Graphics.hpp>

class Object;

class Component
{
protected:
    Object* owner;
public:
    Component(Object* owner) : owner(owner) {}

    virtual void Awake() {};
    virtual void Start() {};
    virtual void Update(float dt) {};
    virtual void LateUpdate(float dt) {};
    virtual void Draw(sf::RenderWindow& window) {};
};

#endif  // COMPONENT_H_