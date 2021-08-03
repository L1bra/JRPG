#ifndef INPUT_H_
#define INPUT_H_

#include "bitmask.h"
#include "command.h"


#include <SFML/Graphics.hpp>


class InputHandler
{
private:
    Bitmask curr_frame_keys;
    Bitmask prev_frame_keys;

    Command* buttonLeft_;
    Command* buttonRight_;
    Command* buttonUp_;
    Command* buttonDown_;

    Command* buttonEsc_;
    Command* buttonEnter_;
public:
    enum class Key
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        ENTER,
        ESC
    };
public:
    InputHandler();
    ~InputHandler();

    // void set_command();

    bool is_key_pressed(Key key_code);
    bool is_key_down(Key key_code);
    bool is_key_up(Key key_code);

    void update();
    Command* handle_input();
};


#endif  // INPUT_H_