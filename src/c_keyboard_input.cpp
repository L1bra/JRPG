#include "c_keyboard_input.h"

C_KeyboardInput::C_KeyboardInput(Object* owner)
    :
    Component(owner),
    index(0)
{
}

void C_KeyboardInput::set_input(InputHandler* input)
{
    this->input = input;
}


void C_KeyboardInput::Update(float dt)
{
    if(input == NULL)
        return;

    (void)dt;

    // TODO:
    if(input->is_key_down(InputHandler::Key::UP))
    {
        // (0 - 1) % 4 = 3
        // (3 - 1) % 4 = 2
        // (2 - 1) % 4 = 1
        // (1 - 1) % 4 = 0

        if(index > 0)
            index = (index - 1) % 4;
            
        // printf("after up index is: %d\n", index);
    }

    if(input->is_key_down(InputHandler::Key::DOWN))
    {
        // (0 + 1) % 4 = 1
        // (1 + 1) % 4 = 2
        // (2 + 1) % 4 = 3
        // (3 + 1) % 4 = 0

        index = (index + 1) % 4;
        
        // printf("after down index is: %d\n", index);
    }

    owner->transform->set_index(index);
}