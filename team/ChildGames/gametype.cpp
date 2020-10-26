#include "gametype.h"

int random(int value)
{
    return rand() % value;
}

int random(int minVal, int maxVal)
{
    return minVal + rand() % (maxVal - minVal);
}
