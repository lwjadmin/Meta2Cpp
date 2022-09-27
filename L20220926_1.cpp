#include "L20220926.h"

int GetRandomNumber(int MinValue, int MaxValue)
{
#ifdef DefineUseMersenTwister
    std::random_device rd;
    std::mt19937 mersentwisterrandom(rd());
    std::uniform_int_distribution<int> GetRandomInt32(MinValue, MaxValue);
    return GetRandomInt32(mersentwisterrandom);
#else
    if (!IsRandInitOnce)
    {
        srand(static_cast<unsigned int) > (time(nullptr)));
        IsRandInitOnce = true;
    }
    return (rand() % MaxValue) + MinValue;
#endif
}

int EventInputNumber(int MinValue, int MaxValue)
{
    bool ValidFlag = false;
    int InputNumber = INT_MIN;
    while (!ValidFlag)
    {
        cout << "Input Number[" << MinValue << " ~ " << MaxValue << "] : "; cin >> InputNumber;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(LLONG_MAX, '\n');
            cout << "Invalid Input. Try Again" << endl;
        }
        else if (InputNumber < MinValue || InputNumber > MaxValue)
        {
            cout << "Invalid Range[" << MinValue << " ~ " << MaxValue << "].Try Again" << endl;
        }
        else
        {
            ValidFlag = true;
        }
    }
    return InputNumber;
}

EnumHighLowState CheckNumberIsHighLow(int NumberOrigin, int NumberCompare)
{
    EnumHighLowState retval = EnumHighLowState::Unknown;
    if (NumberOrigin == NumberCompare)
    {
        cout << "Correct!!" << endl;
        retval = EnumHighLowState::Equal;
    }
    else if (NumberOrigin < NumberCompare)
    {
        cout << "Low!!" << endl;
        retval = EnumHighLowState::Low;
    }
    else if (NumberOrigin > NumberCompare)
    {
        cout << "High!!" << endl;
        retval = EnumHighLowState::High;
    }
    return retval;
}

void FillArrayWithRandomNumbers(int* List, int ListCount, int MinValue, int MaxValue)
{
    int RandomCount = 0;

    while (RandomCount != ListCount)
    {
        bool IsOverlap = false;
        int RandomValue = GetRandomNumber(MinValue, MaxValue);
        for (int i = 0; i < RandomCount; i++)
        {
            if (RandomValue == List[i])
            {
                IsOverlap = true;
                break;
            }
        }
        if (!IsOverlap)
        {
            List[RandomCount++] = RandomValue;
        }
    }
}

void TaskInputNumberIsHighLow()
{
    /*---------------------------------------------------
    1. ��ǻ�Ͱ� ������ ���ڸ� ���Ѵ�.
    2. ������ ���� �Է��� �޾� ���� ���ں��� ������ High, ������ Low��� ����Ѵ�.
    3. ������ �Է��� ���ڰ� ���� ��� Correct��� ����ϰ� ���α׷��� ������.
    ---------------------------------------------------*/
    int RandNumber = GetRandomNumber(1, 100);
    int InputNumber = INT_MIN;
    while (true)
    {
        cout << "RandNum : " << RandNumber << endl;
        InputNumber = EventInputNumber(1, 100);
        if (CheckNumberIsHighLow(RandNumber, InputNumber) == EnumHighLowState::Equal)
        {
            break;
        }
    }
}

bool CheckBullsNCowsResult(int* ListOrigin, int ListOriginCount, int* ListCompare, int ListCompareCount)
{
    bool CorrectFlag = false;
    int BallCount = 0;
    int StrikeCount = 0;

    for (int i = 0; i < ListOriginCount; i++)
    {
        for (int j = 0; j < ListCompareCount; j++)
        {
            if (ListOrigin[i] == ListCompare[j])
            {
                if (i == j)
                {
                    StrikeCount++;
                }
                else
                {
                    BallCount++;
                }
                break;
            }
        }
    }

    if (BallCount == 0 && StrikeCount == 0)
    {
        cout << "Result : " << "OUT!\n";
    }
    else
    {
        if (StrikeCount == 3)
        {
            cout << "Result : " << StrikeCount << "S, Correct!!!\n";
            CorrectFlag = true;
        }
        else
        {
            cout << "Result : " << StrikeCount << "S " << BallCount << "B\n";
        }
    }
    return CorrectFlag;
}

void PrintIntArray(int* Array, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << Array[i] << (i != size - 1 ? "," : "\n");
    }
}

void FillArrayWithPlayerNumbers(int* List, int ListCount, int MinValue, int MaxValue)
{
    int RepCnt = 0;
    while (RepCnt < ListCount)
    {
        cout << "Insert Array[" << RepCnt << "] ";
        List[RepCnt] = EventInputNumber(MinValue, MaxValue);
        RepCnt++;
    }
}

void TaskBullsNCows()
{
    /*--------------------------------------------------------
    1. ��ǻ�Ͱ� 0~9���� �ߺ����� �ʴ� 3�ڸ� ���ڸ� �������� �̾� �迭�� ��´�.
    2. ����ڰ� 0~9���� �ߺ����� �ʴ� 3�ڸ� ���ڸ� �������� �̾� �迭�� ��´�.

    3. �ΰ��� �迭�� ���Ͽ� ���ڴ� ������ ��ġ�� Ʋ���� ��
       ���ڿ� ��ġ�� ������ ��Ʈ����ũ
       ���ڿ� ��ġ�� �ٸ��� �ƿ�
    --------------------------------------------------------*/
    int ComputerList[3] = { 0, };
    int PlayerList[3] = { 0, };
    int ComputerListCount = static_cast<int>(sizeof(ComputerList) / sizeof(int));
    int PlayerListCount = static_cast<int>(sizeof(PlayerList) / sizeof(int));
    int MinValue = 1;
    int MaxValue = 9;
    int CurTurn = 0;
    int MaxTrun = 9;
    bool WinFlag = false;
    FillArrayWithRandomNumbers(ComputerList, ComputerListCount, MinValue, MaxValue);
    cout << "Computer PickList : Hidden\n";

    while (CurTurn < MaxTrun)
    {
        cout << "--Turn [" << CurTurn + 1 << "/" << MaxTrun << "]--------------------------------------" << endl;
        FillArrayWithPlayerNumbers(PlayerList, PlayerListCount, MinValue, MaxValue);
        cout << "Player PickList : ";
        PrintIntArray(PlayerList, PlayerListCount);

        if (CheckBullsNCowsResult(ComputerList, ComputerListCount, PlayerList, PlayerListCount))
        {
            WinFlag = true;
            break;
        }
        CurTurn++;
    }
    cout << "Computer PickList : ";
    PrintIntArray(ComputerList, ComputerListCount);

    if (WinFlag)
    {
        cout << "BullsNCows : You Win!!\n";
    }
    else
    {
        cout << "BullsNCows : You Lose!!\n";
    }
}

int UnrealStyleInitialize()
{
    return GetRandomNumber(1, 100);
}

int UnrealStyleInput()
{
    return EventInputNumber(1, 100);
}

int UnrealStyleProcess(int RandomNumber, int UserNumber)
{
    int retval = -999;
    if (UserNumber == RandomNumber)
    {
        retval = 0;
    }
    else if (UserNumber < RandomNumber)
    {
        retval = 1;
    }
    else
    {
        retval = 2;
    }
    return retval;
}

void UnrealStyleDraw(int ProcessResult)
{
    switch (ProcessResult)
    {
        case 0:
        {
            cout << "EQUAL!!" << endl;
            break;
        }
        case 1:
        {
            cout << "HIGH!!" << endl;
            break;
        }
        case 2:
        {
            cout << "LOW!!" << endl;
            break;
        }
    }
}

void TaskUnrealStyleRun(int RandomNumber)
{
    bool FinishedFlag = false;
    /*-----------------------------------------------------------------
    int Initialize();
    int Input();
    int Process(int RandomNumber, int UserNumber);
    void Draw(int NumberResult);
    void Run(int RandomNumber);
    ------------------------------------------------------------------*/
    while (!FinishedFlag)
    {
        int UserInputNumber = UnrealStyleInput();
        int ProcessResult = UnrealStyleProcess(RandomNumber, UserInputNumber);
        UnrealStyleDraw(ProcessResult);
        if (ProcessResult == 0)
        {
            FinishedFlag = true;
        }
    }
}

int L20220926_1_main(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    //1. �������ڻ̱�
    //TaskInputNumberIsHighLow();
    //2. �߱�����
    TaskBullsNCows();
    //3. �𸮾� �Լ���Ÿ�� �߱�����
    //int RandomNumber = UnrealStyleInitialize();
    //TaskUnrealStyleRun(RandomNumber);
    return 0;
}
