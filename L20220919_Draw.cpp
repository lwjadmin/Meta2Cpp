#include <iostream>
#include "L20220919_Global.h"
#include "L20220919_Draw.h"

using namespace std;

void L20220919_Draw()
{
    for (int i = 0; i < NUMBER; i++)
    {
        int mok = Deck[i] / 13;
        int nmg = Deck[i] % 13;
        switch (mok)
        {
            case 0: { cout << "SPADE"; break; }
            case 1: { cout << "DIAMOND"; break; }
            case 2: { cout << "CLOVER"; break; }
            case 3: { cout << "HEART"; break; }
        }
        cout << " ";
        switch (nmg)
        {
            case 0: { cout << "A"; break; }
            case 10: { cout << "J"; break; }
            case 11: { cout << "Q"; break; }
            case 12: { cout << "K"; break; }
            default: { cout << nmg + 1; }
        }
        cout << endl;

    }
}