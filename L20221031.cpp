#include <iostream>
#include <stack>
#include <conio.h>
#include <thread>
#include <vector>

//#define WASD_MOVE_ENABLED

using namespace std;


int Maze[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,2,1,1,1,1,0,0,0,1},
        {1,0,0,0,1,1,0,1,1,1},
        {1,1,1,0,0,0,0,1,1,1},
        {1,1,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,1,0,1,1,1},
        {1,0,1,1,1,1,0,0,1,1},
        {1,0,1,0,0,0,0,0,3,1},
        {1,1,1,1,1,1,1,1,1,1},
};

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


enum class Direction : int
{
    Right = 0,
    Down = 1,
    Left = 2,
    Up = 3,
    Count = 4
};

enum class ObjectType : int
{
    Floor = 0,
    Wall = 1,
    Player = 2,
    Goal = 3
};



class Point
{
public:
    int X;
    int Y;
    Point(int InX, int InY) : X(InX), Y(InY) {}

    bool Equals(Point pos)
    {
        return X == pos.X && Y == pos.Y;
    }

    void Print()
    {
        cout << "X : " << X << ", Y : " << Y << endl;
    }
};


class VisitedList
{
public:
    VisitedList() {}
    vector<Point> vList;
    void Add(Point newPos)
    {
        for (int i = 0; i < vList.size(); i++)
        {
            if (vList[i].Equals(newPos))
            {
                return;
            }
        }
        vList.push_back(newPos);
    }
    bool Find(Point pos)
    {
        for (int i = 0; i < vList.size(); i++)
        {
            if (vList[i].Equals(pos))
            {
                return true;
            }
        }
        return false;
    }
};

class Player
{
public:
    Point CurPos;
    stack<Point> Visited;
    VisitedList vList;
    Player() : CurPos(1, 1)
    {
        Visited.push(CurPos);
        vList.Add(CurPos);
    }

    void CheckNMove(Direction newdir)
    {
        bool bCanMove = CanMove(newdir);
        if (bCanMove) { Move(newdir); }
    }

    void Move(Direction newdir)
    {
        Point NewPos = GetNextPos(newdir);
        Maze[CurPos.Y][CurPos.X] = (int)ObjectType::Floor;
        Maze[NewPos.Y][NewPos.X] = (int)ObjectType::Player;
        CurPos = NewPos;
        Visited.push(CurPos);
        vList.Add(CurPos);
    }

    bool GoBack()
    {
        bool bCanGoBack = false;
        if (!Visited.empty())
        {
            Point NewPos = Visited.top();
            Maze[CurPos.Y][CurPos.X] = (int)ObjectType::Floor;
            Maze[NewPos.Y][NewPos.X] = (int)ObjectType::Player;
            CurPos = NewPos;
            bCanGoBack = true;
            Visited.pop();
        }
        return bCanGoBack;
    }


    Point GetNextPos(Direction newdir)
    {
        Point NewPos = CurPos;
        switch (newdir)
        {
            case Direction::Up:
            {
                NewPos.Y--;
                break;
            }
            case Direction::Down:
            {
                NewPos.Y++;
                break;
            }
            case Direction::Right:
            {
                NewPos.X++;
                break;
            }
            case Direction::Left:
            {
                NewPos.X--;
                break;
            }
        }
        return NewPos;
    }

    bool CheckVisited(Point NewPos)
    {
        return vList.Find(NewPos);
    }

    bool CanMove(Direction newdir)
    {
        bool bCanMove = false;
        Point NewPos = GetNextPos(newdir);
        return Maze[NewPos.Y][NewPos.X] != (int)ObjectType::Wall ? true : false;
    }
};



void RenderMap()
{
    system("cls");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            switch (Maze[i][j])
            {
                case 0:
                {
                    cout << "  ";
                    break;
                }
                case 1:
                {
                    cout << "¡á";
                    break;
                }
                case 2:
                {
                    cout << "¡Ú";
                    break;
                }
                case 3:
                {
                    cout << "¢Ä";
                    break;
                }
            }
        }
        cout << endl;
    }
}

int L20221031_main(int argc, char* argv[])
{
    Player p1;
    Point GoalPos(8, 8);
    while (true)
    {
        RenderMap();
        if (p1.CurPos.Equals(GoalPos))
        {
            cout << "WAY SUCCESS!" << endl;
            break;
        }
#ifdef WASD_MOVE_ENABLED
        int NewPos = _getch();
        switch (NewPos)
        {
            case 'w':
            {
                p1.CheckNMove(Direction::Up);
                break;
            }
            case 's':
            {
                p1.CheckNMove(Direction::Down);
                break;
            }
            case 'a':
            {
                p1.CheckNMove(Direction::Left);
                break;
            }
            case 'd':
            {
                p1.CheckNMove(Direction::Right);
                break;
            }
        }
#else
        /*-------------------------------------------------------------------------
        -- ±íÀÌ ¿ì¼± Å½»ö(DFS)
        -------------------------------------------------------------------------*/
        bool bMoved = false;
        for (int i = 0; i < (int)Direction::Count; i++)
        {
            Direction newdir = (Direction)i;
            Point newpos = p1.GetNextPos(newdir);
            if (p1.CanMove(newdir) && !p1.CheckVisited(newpos))
            {
                p1.Move(newdir);
                bMoved = true;
                break;
            }
        }
        if (!bMoved)
        {
            if (!p1.GoBack())
            {
                cout << "WAY FAILED!" << endl;
                break;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(500));
#endif
    }
    while (!p1.Visited.empty())
    {
        Point point = p1.Visited.top();
        point.Print();
        p1.Visited.pop();
    }
    return 0;
}