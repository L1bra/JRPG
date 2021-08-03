#ifndef COMMAND_H_
#define COMMAND_H_

#include "entity.h"

class Command
{
public:
    virtual ~Command() {};
    virtual void execute(unsigned int& cursor_index) = 0;
};

#endif  // COMMAND_H_