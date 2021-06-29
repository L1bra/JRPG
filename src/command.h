#ifndef COMMAND_H_
#define COMMAND_H_

#include "entity.h"

class Command
{
public:
    virtual ~Command() {};
    virtual void execute(unsigned int& cursor_index) = 0;
};

class CursorUp: public Command
{
public:
    void execute(unsigned int& cursor_index)
    {
        cursor_index = (cursor_index - 1) % 4;   // debug
    }
};

class CursorDown: public Command
{
public:
    void execute(unsigned int& cursor_index)
    {
        cursor_index = (cursor_index + 1) % 4;
    }
};

#endif  // COMMAND_H_