#pragma once

class Pixel
{
public:
    int X;
    int Y;
    unsigned char R;
    unsigned char G;
    unsigned char B;

    Pixel();
    Pixel(int InX, int InY, unsigned char InR, unsigned char InG, unsigned char InB);
};

