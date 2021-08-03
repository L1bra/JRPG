#include "c_realtime_movement.h"


C_RealtimeMovement::C_RealtimeMovement(Object* owner)
    :
    Component(owner),
    move_speed(100)
{
}

void C_RealtimeMovement::set_input(InputHandler* input)
{
    this->input = input;
}

void C_RealtimeMovement::set_movement_speed(int move_speed)
{
    this->move_speed = move_speed;
}

void C_RealtimeMovement::Update(float dt)
{
    if(input == nullptr)
    {
        return;
    }

    int x_move = 0;

    if(input->is_key_pressed(InputHandler::Key::LEFT))
    {
        x_move = -move_speed;
    }
    else if(input->is_key_pressed(InputHandler::Key::RIGHT))
    {
        x_move = move_speed;
    }

    int y_move = 0;
    if(input->is_key_pressed(InputHandler::Key::UP))
    {
        y_move = -move_speed;
    }
    else if(input->is_key_pressed(InputHandler::Key::DOWN))
    {
        y_move = move_speed;
    }

    float x_frame_move = x_move * dt;
    float y_frame_move = y_move * dt;

    owner->transform->add_position(x_frame_move, y_frame_move);
}