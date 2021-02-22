#include "Random.h"
#include <stdlib.h>
#include <ctime>

float Random::Value01()
{
    return (float)rand() / (RAND_MAX);
}

float Random::Range(float min, float max)
{
    float rand01 = Value01();
    return rand01 * (max - min) + min;
}

void Random::Init()
{
    srand(time(NULL));
}
