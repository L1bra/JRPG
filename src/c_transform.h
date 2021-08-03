#ifndef C_TRANSFORM_H_
#define C_TRANSFORM_H_

#include "component.h"

class C_Transform : public Component
{
private:
    sf::Vector2f position;
    int index;
public:
    C_Transform(Object* owner);
    
    void set_position(float x, float y);
    void set_position(const sf::Vector2f& pos);
    
    void add_position(float x, float y);
    void add_position(sf::Vector2f& pos);

    void set_x(float x);
    void set_y(float y);
    
    void add_x(float x);
    void add_y(float y);

    void set_index(int idx);
    const int& get_index() const;

    const sf::Vector2f& get_position() const;
};


#endif  // C_TRANSFORM_H_