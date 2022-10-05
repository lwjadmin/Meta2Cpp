#include "FC2DGameWorld.h"
#include "FC2DPlayer.h"
#include "GC2DFunctions.h"
#include "FC2DMonster.h"
#include "FC2DGameState.h"

FC2DGameWorld::FC2DGameWorld()
{
    Map = nullptr;
    MapXCols = 30;
    MapYRows = 20;
    Tick = 0;
    Player = nullptr;
    ProcessAFMessage = "";
}

void FC2DGameWorld::Init()
{
    //Generate Map
    Map = new int[MapYRows * MapXCols];
    memset(Map, 0, sizeof(int) * MapYRows * MapXCols);
    for (int y = 0; y < MapYRows; y++)
    {
        for (int x = 0; x < MapXCols; x++)
        {
            int* MapTile = &Map[(y * MapXCols) + x];
            if (y == 0 || y == MapYRows-1)
            {
                *MapTile = (int)EActorType::Wall;
            }
            else
            {
                if (x == 0 || x == MapXCols-1)
                {
                    *MapTile = (int)EActorType::Wall;
                }
                else
                {
                    *MapTile = (int)EActorType::Floor;
                }
            }
        }
    }
    //Generate Monster
    for (int i = 0; i < 5; i++)
    {
        SpawnMonster();
    }
    //Generate Character
    SpawnCharacter();
}

void FC2DGameWorld::SpawnCharacter()
{
    Player = new FC2DPlayer(this);
    Player->SetPosition(1, 1);
    *GetMapTile(1, 1) = (int)EActorType::Player;
}

void FC2DGameWorld::SpawnMonster()
{
    while (true)
    {
        int NewPosX = GetRandNumber(0, MapXCols);
        int NewPosY = GetRandNumber(0, MapYRows);
        if (*GetMapTile(NewPosX, NewPosY) == (int)EActorType::Floor)
        {
            FC2DMonster monster(this);
            monster.InitMonster
            (
                GetRandNumber(50, 100),
                GetRandNumber(100, 200),
                GetRandNumber(2, 10),
                2,
                (EMonsterType)GetRandNumber((int)EMonsterType::Goblin, (int)EMonsterType::Hog)
            );
            monster.SetPosition(NewPosX, NewPosY);
            *GetMapTile(NewPosX, NewPosY) = (int)EActorType::Monster;
            MonsterPool.push_back(monster);
            break;
        }
    }
}

void FC2DGameWorld::Draw()
{
    system("cls");
    cout << "[SYS] Player HP : " << Player->HP << endl;
    cout << "[SYS] Player Gold : " << Player->Gold << endl;
    cout << "[SYS] Monster Count : " << MonsterPool.size() << endl;
    cout << "[SYS] Monster Kill Count : " << Player->MonsterKillCount << endl;
    cout << "[SYS] Tick : " << Tick << endl;

    for (int y = 0; y < MapYRows; y++)
    {
        for (int x = 0; x < MapXCols; x++)
        {
            int* MapTile = &Map[(y * MapXCols) + x];
            switch (*MapTile)
            {
                case (int)EActorType::Wall: { cout << "¡á"; break; }
                case (int)EActorType::Floor: { cout << "  "; break; }
                case (int)EActorType::Player: { cout << "¡Ú"; break; }
                case (int)EActorType::Monster: { cout << "¡Ù"; break;  }
            }
        }
        cout << endl;
    }
    cout << ProcessAFMessage << endl;
    Tick++;
}

int* FC2DGameWorld::GetMapTile(int posX, int posY)
{
    return &Map[(posY * MapXCols) + posX];
}


void FC2DGameWorld::SwapMapTile(int* A, int* B)
{
    int temp = *A;
    *A = *B;
    *B = temp;
}


void FC2DGameWorld::Process(char InputKey, FC2DGameState& GameState)
{
    switch (InputKey)
    {
        case 'D':
        case 'd':
        case 77: //[¢º], MoveRight
        {
            Player->Move(EMoveDirection::East);
            break;
        }
        case 'S':
        case 's':
        case 80: //[¡å], MoveDown
        {
            Player->Move(EMoveDirection::South);
            break;
        }
        case 'A':
        case 'a':
        case 75: //[¢¸], MoveLeft
        {
            Player->Move(EMoveDirection::West);
            break;
        }
        case 'W':
        case 'w':
        case 72: //[¡ã], MoveUp
        {
            Player->Move(EMoveDirection::North);
            break;
        }
        case 32: //[Space], Attack
        {
            Player->Attack();
            break;
        }
        case 27: //[End]
        {
            cout << "End!!" << endl;
            GameState.GameStatus = EGameStatus::END;
            break;
        }
    }

    for (int i = MonsterPool.size() - 1; i >= 0; i--) 
    {
        FC2DMonster* monster = &MonsterPool[i];
        if (!monster->isAlive)
        {
            monster->Dead();
            MonsterPool.erase(MonsterPool.begin() + i);
        }
        else
        {
            EMoveDirection newDirection = (EMoveDirection)(GetRandNumber(0, 3) * 90);
            monster->Move(newDirection);
            monster->Attack(Player);
        }
    }
    if (!Player->isAlive)
    {
        GameState.GameStatus = EGameStatus::END;
        return;
    }

    if (Tick > 10)
    {
        Tick = 0;
        SpawnMonster();
    }
}

FC2DGameWorld::~FC2DGameWorld()
{
    delete[] Map;
}