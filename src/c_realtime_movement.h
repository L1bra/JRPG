#ifndef C_KEYBOARD_MOVEMENT_H_
#define C_KEYBOARD_MOVEMENT_H_

#include "object.h"
#include "component.h"
#include "input.h"


class C_RealtimeMovement : public Component
{
private:
    int move_speed;
    InputHandler* input;
public:
    C_RealtimeMovement(Object* owner);

    void set_input(InputHandler* input);
    void set_movement_speed(int move_speed);
    void Update(float dt) override;
};

#endif  // C_KEYBOARD_MOVEMENT_H_