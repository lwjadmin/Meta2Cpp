#include "EC2DDefine.h"
#include "FC2DGameWorld.h"
#include "FC2DGameState.h"

int C2DGameMain()
{
    FC2DGameWorld GMWorld;
    FC2DGameState GMState;

    GMWorld.Init();

    while (true)
    {

        GMWorld.Draw();
        GMWorld.Process(_getch(), GMState);
        if (GMState.GameStatus == EGameStatus::END)
        {
            cout << "YOU DIED!!!!" << endl;
            break;
        }
    }
    return 0;
}

int C2DGameMain_main(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    return C2DGameMain();
}


