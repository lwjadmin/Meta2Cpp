#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Prob2557() {
	std::cout << "Hello World!" << std::endl;
}

void Prob10718() {
	std::cout << "강한친구 대한육군" << std::endl;
	std::cout << "강한친구 대한육군" << std::endl;
}

void Prob1000() {
	int a;
	int b;
	int result;
	cin >> a >> b;
	result = a + b;
	cout << result;
}

void Prob1001() {
	int a;
	int b;
	int result;
	cin >> a >> b;
	result = a - b;
	cout << result;
}

void Prob10998_Multiply() {
	int a;
	int b;
	int result;
	cin >> a >> b;
	result = a * b;
	cout << result;
}

void Prob1008_Divide() {
	int a = 0;
	int b = 0;
	double result = 0;
	std::cin >> a >> b;

	result = static_cast<double>(a) / static_cast<double>(b);
	//double형의 정밀도 : 12
	std::cout.precision(12);
	std::cout << result;
}

void Prob10869() {
	int a = 0;
	int b = 0;
	cin >> a >> b;

	cout << a + b << endl;
	cout << a - b << endl;
	cout << a * b << endl;
	cout << a / b << endl;
	cout << a % b << endl;

}

void Prob10926_Append() {
	std::string strID;
	getline(cin, strID);

	strID.append("??!");
	std::cout << strID;
}

void Prob18108_yearADD() {
	int year = 0;
	cin >> year;
	year = year - 543;
	cout << year;
}

void Prob18108_chesspiece() {
	/*-----------------------------------
	체스 : 16개 피스, 킹1, 퀸1, 룩2, 비숍2, 나이트2, 폰8
	-----------------------------------*/
	int chesspieceOrigin[6] = { 1,1,2,2,2,8 };
	int chesspieceInput[6] = { 0, };

	cin >> chesspieceInput[0] >> chesspieceInput[1] >> chesspieceInput[2] >>
		chesspieceInput[3] >> chesspieceInput[4] >> chesspieceInput[5];

	for (int i = 0; i < 6; i++) {
		chesspieceInput[i] = (chesspieceInput[i] - chesspieceOrigin[i]) * -1;
		cout << chesspieceInput[i] << (i < 5 ? " " : "\n");
	}


}

void Prob2480_ThreeDice()
{
	int dice1 = 0;
	int dice2 = 0;
	int dice3 = 0;
	int money = 0;

	int maxdice = 0;

	cin >> dice1 >> dice2 >> dice3;

	if (dice1 == dice2 && dice2 == dice3 && dice3 == dice1)
	{
		money = 10000 + (dice1 * 1000);
	}
	else if (dice1 != dice2 && dice2 != dice3 && dice3 != dice1)
	{
		maxdice = dice1;
		maxdice = maxdice > dice2 ? maxdice : dice2;
		maxdice = maxdice > dice3 ? maxdice : dice3;
		money = maxdice * 100;
	}
	else
	{
		if (dice1 == dice2)
		{
			money += dice1 * 100;
		}
		else if (dice2 == dice3)
		{
			money += dice2 * 100;
		}
		else if (dice3 == dice1)
		{
			money += dice3 * 100;
		}
		money += 1000;
	}
	cout << money;
}

void Prob2739_gugudan()
{
	int dan = 0;
	cin >> dan;
	for (int i = 1; i <= 9; i++)
	{
		cout << dan << " * " << i << " = " << dan * i << endl;
	}
}


void Prob10950_APlusB()
{
	
	vector<int> vlist;
	int ncount = 0;

	int a = 0;
	int b = 0;
	cin >> ncount;
	int* arr = (int*)malloc(sizeof(int) * ncount);
	if (arr != nullptr)
	{
		for (int i = 0; i < ncount; i++)
		{
			cin >> a >> b;
			arr[i] = a + b;
		}
		for (int i = 0; i < ncount; i++)
		{
			cout << arr[i] << endl;
		}
	}
	free(arr);
}

void Prob8393_AddAll()
{
	int number = 0;
	cin >> number;
	cout << (number * (number + 1)) / 2 << endl;

}



void Prob25304_Receipt()
{
	int totValue = 0;
	int nCount = 0;
	int nVal = 0;
	int nCnt = 0;
	int cmpValue = 0;
	cin >> totValue;
	cin >> nCount;

	for (int i = 0; i < nCount; i++)
	{
		cin >> nVal >> nCnt;
		cmpValue += (nVal * nCnt);
	}
	cout << (totValue == cmpValue ? "Yes" : "No") << endl;

}