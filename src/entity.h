#ifndef ENTITY_H_
#define ENTITY_H_

#include "resource_manager.h"
#include "random_gen.h"

#include <SFML/Graphics.hpp>
#include <memory>


enum class Entity_state : uint8_t
{
    Dead = 0,
    Alive
};


enum class Alive_state : uint8_t
{
    Stand = 0,
    Walking
};

class Entity
{
public:
    virtual ~Entity() {};

    // virtual void move() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(float dt) = 0;
};

#endif  // ENTITY_H_