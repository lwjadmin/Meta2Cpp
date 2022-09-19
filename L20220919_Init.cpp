#include <iostream>
#include "L20220919_Global.h"
#include "L20220919_Init.h"

using namespace std;


void L20220919_Init()
{
    for (int i = 0; i < NUMBER; i++)
    {
        Deck[i] = i;
    }
}