#pragma once
#include <random>
#define DefineUseMersenTwister

#ifndef DefineUseMersenTwister
bool IsRandInitOnce = false;
#endif

int GetRandNumber(int MinValue, int MaxValue)
{
#ifdef DefineUseMersenTwister
    std::random_device rd;
    std::mt19937 mersentwisterrandom(rd());
    std::uniform_int_distribution<int> GetRandomInt32(MinValue, MaxValue);
    return GetRandomInt32(mersentwisterrandom);
#else
    if (!IsRandInitOnce)
    {
        srand(static_cast<unsigned int) > (time(nullptr)));
        IsRandInitOnce = true;
    }
    return (rand() % MaxValue) + MinValue;
#endif
}