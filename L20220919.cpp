#include <iostream>
#include <sstream>

using namespace std;

const int RAND_NUMBER_COUNT = 100;
const int TRUMP_CARD_SIZE = 52;

#ifdef __USE_MT19937__
#include <random>
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> rndval(0, TRUMP_CARD_SIZE - 1);
std::uniform_int_distribution<int> rndval(0, RAND_NUMBER_COUNT);
#endif // __USE_MT19937__


int Prob1_Factorial(int n)
{
    int sum = 1;
    for (int i = n; i > 0; i--)
    {
        sum *= i;
    }
    return sum;
}

void Prob2_Printgugudan(int n)
{
    for (int i = 1; i <= 9; i++)
    {
        cout << n << " * " << i << " = " << i * n << endl;
    }
}

void Prob3_RandNumber()
{
    int visited[100] = { 0, };
    int ncount = 0;
    while (true)
    {
        int rndnum = (rand() % 100) + 1;
        if (visited[rndnum - 1] != 1)
        {
            visited[rndnum - 1] = 1;
            cout << rndnum << " ";
            ncount++;
        }
        if (ncount == 100) { break; }
    }
}

void Prob4_PrintCard(int cardNo)
{
    int rows = cardNo / 13;
    int cols = cardNo % 13;

    if (cardNo < 0)
    {
        cout << "[ERR]Invalid Card" << endl;
    }
    else
    {
        switch (rows)
        {
            case 0: { cout << "[♠]Spade "; break; }
            case 1: { cout << "[◇]Diamond "; break; }
            case 2: { cout << "[♣]Clover "; break; }
            case 3: { cout << "[♡]Heart "; break; }
        }
        switch (cols)
        {
            case 0: { cout << "A" << endl; break; }
            case 10: { cout << "J" << endl; break; }
            case 11: { cout << "Q" << endl; break; }
            case 12: { cout << "K" << endl; break; }
            default: { cout << (cols + 1) << endl; ; }
        }
        if (cols == 0)
        {
            cout << "A" << endl;
        }
        else if (cols == 10)
        {
            cout << "J" << endl;
        }
        else if (cols == 11)
        {
            cout << "Q" << endl;
        }
        else if (cols == 12)
        {
            cout << "K" << endl;
        }
        else
        {
            cout << cols + 1 << endl;
        }
        
    }
}

void Prob4_GetTrumpCard()
{
    bool bPeek[TRUMP_CARD_SIZE] = { 0, };

    int ncount = 0;
    while (true)
    {
        int randCardNo = (rand() % 52);
        if (bPeek[randCardNo] == false)
        {
            bPeek[randCardNo] = true;
            Prob4_PrintCard(randCardNo);
            ncount++;
        }
        if (ncount == 4) { break; }
    }
}

void Prob3_RandNumber_Shuffle(int shuffleCount = (RAND_NUMBER_COUNT / 2))
{
#ifndef __USE_MT19937__
    srand(static_cast<unsigned int>(time(nullptr)));
#endif // !1

    

    int numbers[RAND_NUMBER_COUNT];
    for (int i = 0; i < RAND_NUMBER_COUNT; i++)
    {
        numbers[i] = i + 1;
    }
    while (shuffleCount > 0)
    {
#ifndef __USE_MT19937__
        
        int rand1 = rand() % RAND_NUMBER_COUNT;
        int rand2 = rand() % RAND_NUMBER_COUNT;
#else
        int rand1 = rndval(mt) % RAND_NUMBER_COUNT;
        int rand2 = rndval(mt) % RAND_NUMBER_COUNT;
#endif // !__USE_MT19937__

        
        if (rand1 != rand2)
        {
            int temp = numbers[rand1];
            numbers[rand1] = numbers[rand2];
            numbers[rand2] = temp;
            shuffleCount--;
        }
    }
    for (int i = 0; i < RAND_NUMBER_COUNT; i++)
    {
        cout << numbers[i] << (i != RAND_NUMBER_COUNT - 1 ? "," : "\n");
    }
}




/// <summary>
/// 카드모양을 출력하고, 카드값을 반환한다.
/// </summary>
/// <param name="CardIndex">
/// <para/>Range : 00 ~ 51
/// <para/>[♠]SPADE    A,1...,10,J,Q,K[00~12]
/// <para/>[◆]DIAMOND A,1...,10,J,Q,K[13~25]
/// <para/>[♣]CLOVER   A,1...,10,J,Q,K[26~38]
/// <para/>[♥]HEART    A,1...,10,J,Q,K[39~51]
/// </param>
/// <returns>CardValue[1~10]</returns>
string Blackjack_GetCardString(int CardIndex, int* CardVal = nullptr)
{
    string strout = "";
    if (CardVal != nullptr) { *CardVal = -1; }

    int CardRows = CardIndex / 13;
    int CardCols = CardIndex % 13;

    if (CardIndex >= 0)
    {
        switch (CardRows)
        {
            case 0: { strout += "[(♠)SPADE"; break; }
            case 1: { strout += "[(◆)DIAMOND"; break; }
            case 2: { strout += "[(♣)CLOVER"; break; }
            case 3: { strout += "[(♥)HEART"; break; }
        }
        strout += " ";
        switch (CardCols)
        {
            case 0: { strout += "A(1/10)]";  break; }
            case 9: { strout += "10(10)]";  break; }
            case 10: { strout += "JUMP(10)]";  break; }
            case 11: { strout += "QUEEN(10)]";  break; }
            case 12: { strout += "KING(10)]"; break; }
            default:
            {
                strout += (CardCols + 1 + '0');
                strout += "(";
                strout += (CardCols + 1 + '0');
                strout += ")]";
            }
        }
        if (CardVal != nullptr)
        {
            if (CardCols >= 9)
            {
                *CardVal = 10;
            }
            else
            {
                *CardVal = CardCols + 1;
            }
        }
    }
    return strout;
}

int Blackjack_PickCard(bool* PickList, int& PickedCount)
{
    if (PickedCount == 0)
    {
        //CASE 1 : using rand()
        srand(static_cast<unsigned int>(time(nullptr)));
    }
    int CardVal = -1;
    while (true)
    {
        if (PickedCount >= TRUMP_CARD_SIZE)
        {
            break;
        }
        else
        {
#ifdef __USE_MT19937__
            CardVal = rndval(mt) % 52; //00 ~ 51
#else
            CardVal = (rand() % TRUMP_CARD_SIZE); //00 ~ 51
#endif // __USE_MT19937__

            if (PickList[CardVal] == false)
            {
                PickList[CardVal] = true;
                PickedCount++;
                break;
            }
        }
    }
    return CardVal;
}

void Blackjack_PrintDeck(bool PlayerYN, int* DeckList, int DeckCount, bool ShowAllYN = true)
{
    int totalValue = 0;
    cout << (PlayerYN ? "[SYS] Player Deck Count : " : "[SYS]Dealer Deck Count : ") << DeckCount << endl;

    for (int i = 0; i < DeckCount; i++)
    {
        cout << Blackjack_GetCardString(DeckList[i], nullptr);

        cout << (i != DeckCount - 1 ? "," : "\n");
    }
}

int Blackjack_Play()
{
    int ResultVal = -1;

    int PlayerDeck[10];
    memset(PlayerDeck, -1, sizeof(PlayerDeck));
    int PlayerPoint = 0;
    int DealerDeck[10];
    memset(DealerDeck, -1, sizeof(DealerDeck));
    int DealerPoint = 0;
    bool TRUMP_PICK_LIST[TRUMP_CARD_SIZE] = { 0, };
    int TRUMP_PICK_COUNT = 0;

    int Turn = 0;
    int PlayerCommand = 0;
    bool bExitCalled = false;

    PlayerDeck[Turn] = Blackjack_PickCard(TRUMP_PICK_LIST, TRUMP_PICK_COUNT);
    DealerDeck[Turn++] = Blackjack_PickCard(TRUMP_PICK_LIST, TRUMP_PICK_COUNT);
    PlayerDeck[Turn] = Blackjack_PickCard(TRUMP_PICK_LIST, TRUMP_PICK_COUNT);
    DealerDeck[Turn++] = Blackjack_PickCard(TRUMP_PICK_LIST, TRUMP_PICK_COUNT);

    while (!bExitCalled)
    {
        system("cls");
        Blackjack_PrintDeck(true, PlayerDeck, Turn, true);
        cout << endl;
        Blackjack_PrintDeck(false, DealerDeck, Turn, false);
        cout << endl;

        cout << "[INP] [Turn " << (Turn - 1) << "] 1:Hit,2:Stay = ";
        cin >> PlayerCommand;
        switch (PlayerCommand)
        {
            case 1: //Hit, 카드를 한장 더 받는다.
            {
                PlayerDeck[Turn] = Blackjack_PickCard(TRUMP_PICK_LIST, TRUMP_PICK_COUNT);
                DealerDeck[Turn++] = Blackjack_PickCard(TRUMP_PICK_LIST, TRUMP_PICK_COUNT);
                break;
            }
            case 2: //Stay, 카드를 비교한다.
            {
                for (int i = 0; i < Turn; i++)
                {
                    int CardVal = 0;
                    if (PlayerDeck[i] == 0)
                    {
                        cout << "[INP] 다음 ACE 카드 : ";
                        cout << Blackjack_GetCardString(PlayerDeck[i]);
                        cout << " 를 11로 계산하시겠습니까? 1:Y,2:N : ";
                        cin >> PlayerCommand;
                        PlayerPoint += (PlayerCommand == 1 ? 11 : 1);
                    }
                    else
                    {
                        Blackjack_GetCardString(PlayerDeck[i], &CardVal);
                        PlayerPoint += CardVal;
                    }
                    Blackjack_GetCardString(DealerDeck[i], &CardVal);
                    DealerPoint += CardVal;
                }

                cout << "[SYS] PlayerPoint : " << PlayerPoint << endl;
                cout << "[SYS] DealerPoint : " << DealerPoint << endl;

                PlayerPoint = PlayerPoint - 21;
                PlayerPoint = PlayerPoint < 0 ? PlayerPoint * -1 : PlayerPoint;

                DealerPoint = DealerPoint - 21;
                DealerPoint = DealerPoint < 0 ? DealerPoint * -1 : DealerPoint;

                //판정시작
                if (PlayerPoint == DealerPoint)
                {
                    cout << "[SYS] DRAW" << endl;
                    ResultVal = 1;
                }
                else if (PlayerPoint < DealerPoint)
                {
                    cout << "[SYS] YOU WIN" << endl;
                    ResultVal = 2;
                }
                else if (PlayerPoint > DealerPoint)
                {
                    cout << "[SYS] YOU LOSE" << endl;
                    ResultVal = 3;
                }
                bExitCalled = true;
                break;
            }
        }
    }
    return ResultVal;
}

void Blackjack_PressEnterToContinue()
{
    cin.clear();
    cin.ignore(LLONG_MAX, '\n');
    cout << "[SYS] 계속하려면 엔터키를 누르세요." << endl;
    string str;
    getline(cin, str);

}

void Blackjack_Main()
{
    int WinCount = 0;
    int LoseCount = 0;
    int DrawCount = 0;
    while (!cin.eof())
    {
        switch (Blackjack_Play())
        {
            case 1:
            {
                DrawCount++;
                break;
            }
            case 2:
            {
                WinCount++;
                break;
            }
            case 3:
            {
                LoseCount++;
                break;
            }
        }

        cout << "[SYS] WinCount = " << WinCount << ",";
        cout << "LoseCount = " << LoseCount << ",";
        cout << "DrawCount = " << DrawCount << endl;
        Blackjack_PressEnterToContinue();
    }
}

int t20220919_main()
{
    Prob3_RandNumber_Shuffle();
    return 0;
}