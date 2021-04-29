#include "random_gen.h"

float Random::float_range(float start, float end)
{
    return float(rand() % ((int)end + 1 - (int)start)) + (int)start;
}
