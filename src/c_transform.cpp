#include "c_transform.h"

C_Transform::C_Transform(Object* owner)
    :
    Component(owner),
    position(0.f, 0.f),
    index(0)
{
}

void C_Transform::set_position(float x, float y)
{
    position.x = x;
    position.y = y;
}

void C_Transform::set_position(const sf::Vector2f& pos)
{
    position = pos;
}

void C_Transform::add_position(float x, float y)
{
    position.x += x;
    position.y += y;
}

void C_Transform::add_position(sf::Vector2f& pos)
{
    position += pos;
}

void C_Transform::set_x(float x)
{
    position.x = x;
}

void C_Transform::set_y(float y)
{
    position.y = y;
}

void C_Transform::add_x(float x)
{
    position.x += x;
}

void C_Transform::add_y(float y)
{
    position.y += y;
}

void C_Transform::set_index(int index)
{
    this->index = index;
}

const int& C_Transform::get_index() const
{
    return this->index;
}

const sf::Vector2f& C_Transform::get_position() const
{
    return position;
}