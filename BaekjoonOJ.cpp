#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace	std;

bool Prob1065_isHansu(int number)
{
    bool isHansu = true;
    vector<int> v;
    int idx = 0;
    if (number >= 100)
    {
        while (true)
        {
            if (number == 0) { break; }
            v.insert(v.begin(), (number % 10));
            number = number / 10;
            idx++;
        }
        int gongcha_fst = v[1] - v[0];
        for (int i = 1; i < v.size();i++)
        {
            int gongcha_nxt = 2;
            if (gongcha_fst != gongcha_nxt)
            {
                isHansu = false;
                break;
            }
        }
    }
    
    return isHansu;
}

void Prob1065_Hansu()
{
    //int ncount;
    //cin >> ncount;
    for (int i = 1000; i <= 1200; i++)
    {
        Prob1065_isHansu(i);
    }
}


int main()
{
    Prob1065_Hansu();
}