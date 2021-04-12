#include "random_gen.h"

float Random::float_range(int start, int end)
{
    return (rand() % (end + 1 - start)) + start;
}
