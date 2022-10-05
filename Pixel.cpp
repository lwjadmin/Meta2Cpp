#include "Pixel.h"

//#define USE_MEMBER_INITALIZER_LISTS

Pixel::Pixel()
{
    X = 0;
    Y = 0;
    R = 0;
    G = 0;
    B = 0;
}

Pixel::Pixel(int InX, int InY, unsigned char InR, unsigned char InG, unsigned char InB)
#ifdef USE_MEMBER_INITALIZER_LISTS
    : X(InX), Y(InY), R(InR), G(InG), B(InB)
#endif
{
#ifndef USE_MEMBER_INITALIZER_LISTS
    X = InX;
    Y = InY;
    R = InR;
    G = InG;
    B = InB;
#endif
}
