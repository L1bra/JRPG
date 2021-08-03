#include "input.h"

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::update()
{
    prev_frame_keys.set_mask(curr_frame_keys);

    curr_frame_keys.set_bit((int)Key::LEFT,
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::A)));

    curr_frame_keys.set_bit((int)Key::RIGHT,
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::D)));

    curr_frame_keys.set_bit((int)Key::UP,
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::W)));

    curr_frame_keys.set_bit((int)Key::DOWN,
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ||
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::S)));

    curr_frame_keys.set_bit((int)Key::ESC),
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

    curr_frame_keys.set_bit((int)Key::ENTER),
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}

// is_key_pressed for real time input
// is_key_down or is_key_up for single input
Command* InputHandler::handle_input()
{
    if(is_key_down(Key::LEFT)) return buttonLeft_;
    if(is_key_down(Key::RIGHT)) return buttonRight_; 
    if(is_key_down(Key::UP)) return buttonUp_;
    if(is_key_down(Key::DOWN)) return buttonDown_;

    return NULL;
}


bool InputHandler::is_key_pressed(Key key_code)
{
    return curr_frame_keys.get_bit((int)key_code);
}


bool InputHandler::is_key_down(Key key_code)
{
    bool prev_frame = prev_frame_keys.get_bit((int)key_code);
    bool curr_frame = curr_frame_keys.get_bit((int)key_code);

    return curr_frame && !prev_frame;
}


bool InputHandler::is_key_up(Key key_code)
{
    bool prev_frame = prev_frame_keys.get_bit((int)key_code);
    bool curr_frame = curr_frame_keys.get_bit((int)key_code);

    return !curr_frame && prev_frame;
}