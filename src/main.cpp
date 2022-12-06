#include "application.h"


int main(int argc, char* argv[])
{
    Application game;
    if (!game.init()) return -1;
    game.start();

    return 0;
}