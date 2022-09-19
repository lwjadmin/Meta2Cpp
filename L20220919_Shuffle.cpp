#include <iostream>
#include "L20220919_Global.h"
#include "L20220919_Shuffle.h"

using namespace std;

void L20220919_Shuffle()
{
    int shuffleCount = (NUMBER / 2) + 1;
    while (shuffleCount > 0)
    {
        int rand1 = rand() % NUMBER;
        int rand2 = rand() % NUMBER;

        if (rand1 != rand2)
        {
            int temp = Deck[rand1];
            Deck[rand1] = Deck[rand2];
            Deck[rand2] = temp;
            shuffleCount--;
        }
    }
}