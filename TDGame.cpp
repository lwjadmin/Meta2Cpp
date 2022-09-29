#include <iostream>

using namespace std;

void Prob1417_Election()
{
    //국회의원수
    int candidateCnt = 0;
    //득표수
    int* electionBasket = nullptr;
    //국회의원 수 입력
    cin >> candidateCnt;
    electionBasket = new int[candidateCnt];
    //득표수 입력
    for (int i = 0; i < candidateCnt; i++)
    {
        cin >> electionBasket[i];
    }
    //최다득표 국회의원 
    int MaxCandidateIdx = 0;
    //최다득표 국회의원 득표수
    int MaxCandidateCnt = 0;
    //돈 횟수
    int count = 0;
    
    while (true)
    {
        bool bWin = true;
        for (int i = 1; i < candidateCnt; i++)
        {
            if (electionBasket[i] >= electionBasket[0])
            {
                bWin = false;
                break;
            }
        }
        if (bWin) { break; }
        for (int i = 1; i < candidateCnt; i++)
        {
            if (i == 1)
            {
                MaxCandidateIdx = 1;
            }
            else if(electionBasket[MaxCandidateIdx] < electionBasket[i])
            {
                MaxCandidateIdx = i;
            }
        }
        electionBasket[MaxCandidateIdx] -= 1;
        electionBasket[0] += 1;
        count += 1;
    }
    delete[] electionBasket;
    std::cout << count;
}

int main(void)
{
    Prob1417_Election();
    return 0;
}

namespace TDG
{

    int* Map = nullptr;

    enum class TileType : int
    {
        Unknown = 0,
        Wall = 1,
        Floor = 2,
        Player = 3,
        Goal = 4
    };

    const int MapRows = 30;
    const int MapCols = 50;

    int PlayerPosX = 1;
    int PlayerPosY = 1;

    int GoalPosX = MapCols - 2;
    int GoalPosY = MapRows - 2;


    void Init()
    {
        Map = new int[MapRows * MapCols];
        memset(Map, (int)TDG::TileType::Unknown, sizeof(int) * MapRows * MapCols);
        for (int i = 0; i < MapRows; i++)
        {
            for (int j = 0; j < MapCols; j++)
            {
                int* tile = &Map[(i * MapCols) + j];

                if (PlayerPosX == j && PlayerPosY == i)
                {
                    *tile = (int)TDG::TileType::Player;
                    continue;
                }
                if (GoalPosX == j && GoalPosY == i)
                {
                    *tile = (int)TDG::TileType::Goal;
                    continue;
                }

                if (i == 0 || i == MapRows - 1)
                {
                    *tile = (int)TDG::TileType::Wall;
                }
                else
                {
                    if (j == 0 || j == MapCols - 1)
                    {
                        *tile = (int)TDG::TileType::Wall;
                    }
                    else
                    {
                        *tile = (int)TDG::TileType::Floor;
                    }
                }
            }
        }
    }

    void Draw()
    {
        for (int i = 0; i < MapRows; i++)
        {
            for (int j = 0; j < MapCols; j++)
            {
                int* tile = &Map[(i * MapCols) + j];

                switch (*tile)
                {
                    case (int)TDG::TileType::Wall:
                    {
                        cout << "□"; break;
                    }
                    case (int)TDG::TileType::Floor:
                    {
                        cout << "  "; break;
                    }
                    case (int)TDG::TileType::Player:
                    {
                        cout << "★"; break;
                    }
                    case (int)TDG::TileType::Goal:
                    {
                        cout << "◐"; break;
                    }
                }
            }
            cout << endl;
        }
    }
}



