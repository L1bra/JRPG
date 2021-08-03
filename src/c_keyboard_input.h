#ifndef C_KEYBOARD_INPUT_H_
#define C_KEYBOARD_INPUT_H_

#include "object.h"
#include "component.h"
#include "input.h"

class C_KeyboardInput : public Component
{
private:
    int index;
    InputHandler* input;
public:
    C_KeyboardInput(Object* owner);

    void set_input(InputHandler* input);

    void Update(float dt) override;

};

#endif  // C_KEYBOARD_INPUT_H_