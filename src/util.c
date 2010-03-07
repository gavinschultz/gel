#include    "util.h"

float square(float n)
{
    return n*n;
}

int rand_sign()
{
    return (rand() % 2 ? -1 : 1);
}

float randf(float limit)
{
    return (float)rand()/(float)RAND_MAX * limit;
}

float wrapf(float value, float limit)
{
    if (value >= limit)
        return value - limit;
    else if (value < 0.0f)
        return value + limit;
    else
        return value;
}
