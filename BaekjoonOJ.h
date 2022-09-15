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


void Prob15552_SpeedAPlusB()
{
	/*-----------------------------------------------------
	본격적으로 for문 문제를 풀기 전에 주의해야 할 점이 있다.
	입출력 방식이 느리면 여러 줄을 입력받거나 출력할 때 시간초과가 날 수 있다는 점이다.
	C++을 사용하고 있고 cin/cout을 사용하고자 한다면, cin.tie(NULL)과
	sync_with_stdio(false)를 둘 다 적용해 주고, endl 대신 개행문자(\n)를 쓰자.
	단, 이렇게 하면 더 이상 scanf/printf/puts/getchar/putchar 등 C의 입출력 방식을
	사용하면 안 된다.
	-----------------------------------------------------*/
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int nCount;
	int a, b;

	cin >> nCount;
	for (int i = 0; i < nCount; i++)
	{
		cin >> a >> b;
		cout << a + b << '\n';
	}
}


void Prob11021_SpeedAPlusB2()
{
	/*-----------------------------------------------------
	본격적으로 for문 문제를 풀기 전에 주의해야 할 점이 있다.
	입출력 방식이 느리면 여러 줄을 입력받거나 출력할 때 시간초과가 날 수 있다는 점이다.
	C++을 사용하고 있고 cin/cout을 사용하고자 한다면, cin.tie(NULL)과
	sync_with_stdio(false)를 둘 다 적용해 주고, endl 대신 개행문자(\n)를 쓰자.
	단, 이렇게 하면 더 이상 scanf/printf/puts/getchar/putchar 등 C의 입출력 방식을
	사용하면 안 된다.
	-----------------------------------------------------*/
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int nCount;
	int a, b;

	cin >> nCount;
	for (int i = 0; i < nCount; i++)
	{
		cin >> a >> b;
		cout << "Case #" << i + 1 << ": " << a + b << '\n';
	}
}

void Prob11022_SpeedAPlusB3()
{
	/*-----------------------------------------------------
	본격적으로 for문 문제를 풀기 전에 주의해야 할 점이 있다.
	입출력 방식이 느리면 여러 줄을 입력받거나 출력할 때 시간초과가 날 수 있다는 점이다.
	C++을 사용하고 있고 cin/cout을 사용하고자 한다면, cin.tie(NULL)과
	sync_with_stdio(false)를 둘 다 적용해 주고, endl 대신 개행문자(\n)를 쓰자.
	단, 이렇게 하면 더 이상 scanf/printf/puts/getchar/putchar 등 C의 입출력 방식을
	사용하면 안 된다.
	-----------------------------------------------------*/
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int nCount;
	int a, b;

	cin >> nCount;
	for (int i = 0; i < nCount; i++)
	{
		cin >> a >> b;
		cout << "Case #" << i + 1 << ": " << a << " + " << b << " = " << a + b << '\n';
	}
}

void Prob2438_PrintStar()
{
	int nCount;
	cin >> nCount;
	for (int i = 0; i < nCount; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
}

void Prob10871_LessthenX()
{
	int nCount = 0;
	int X = 0;
	cin >> nCount >> X;

	int numbers = 0;

	for (int i = 0; i < nCount; i++)
	{
		cin >> numbers;
		if (numbers < X)
		{
			cout << numbers << " ";
		}
	}
}


void Prob10952_APlusBwhile()
{
	int a = -1, b = -1;
	while (true)
	{
		cin >> a >> b;
		if (a == 0 && b == 0) { break; }
		cout << a + b << endl;
	}
}

void Prob10951_APlusB()
{
	int a, b;
	vector<int> v1;
	while (true)
	{
		cin >> a >> b;
		if (cin.eof())
		{
			break;
		}
		else
		{
			v1.push_back(a + b);
		}
	}
	for (int v : v1)
	{
		cout << v << '\n';
	}
}

void Prob1110_PlusCycle()
{
	int original_value = 0;
	int new_value = 0;
	int nCount = 0;
	int num10 = 0;
	int num1 = 0;
	cin >> original_value; //26

	new_value = original_value;
	do
	{
		num10 = new_value / 10; //2
		num1 = new_value % 10; //6
		new_value = (num1 * 10) + ((num10 + num1) % 10);
		nCount++;
	} while (original_value != new_value);
	cout << nCount;
}


void Prob10818_GetMinMax()
{
	int nCount = 0;
	cin >> nCount;
	int ival = 0;
	int min = 0;
	int max = 0;
	for (int i = 0; i < nCount; i++)
	{
		cin >> ival;
		if (i == 0)
		{
			min = max = ival;
		}
		else
		{
			max = ival > max ? ival : max;
			min = ival < min ? ival : min;
		}
	}
	cout << min << " " << max;
}


void Prob2562_GetMax()
{
	int max = 0;
	int maxidx = 0;
	int value = 0;

	for (int i = 0; i < 9; i++)
	{
		cin >> value;
		if (i == 0)
		{
			max = value;
			maxidx = i + 1;
		}
		else if (i > 0 && value > max)
		{
			max = value;
			maxidx = i + 1;
		}
	}
	cout << max << endl;
	cout << maxidx << endl;
}

void Prob3052_NMG()
{
	int number = 0;
	int tnmg = 0;
	int nmg[10] = { 0, };
	int nmgcnt = 0;
	for (int i = 0; i < 10; i++)
	{
		cin >> number;
		tnmg = number % 42;
		nmg[i] = tnmg;
		for (int j = 0; j < i; j++)
		{
			if (tnmg == nmg[j])
			{
				tnmg = 999;
				break;
			}
		}
		if (tnmg != 999) { nmgcnt++; }
	}

	cout << nmgcnt << endl;
}

void Prob1546_average()
{
	int ncount = 0;
	cin >> ncount;
	int arr[1000] = { 0, };
	int max = 0;
	double tot = 0;
	for (int i = 0; i < ncount; i++)
	{
		cin >> arr[i];
		if (i == 0)
		{
			max = arr[i];
		}
		else if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	for (int i = 0; i < ncount; i++)
	{
		tot += (arr[i] / (double)max) * 100;
	}
	cout.precision(12);
	cout << tot / (double)ncount << endl;
}

void Prob8958_OXQuiz()
{
	int nCount = 0;
	cin >> nCount;
	cin.clear();
	//cin.ignore(LLONG_MAX, '\n');
	cin.ignore(100, '\n'); //백준에서는 LLONG_MAX define을 몰라서 넉넉히 100주자.
	for (int i = 0; i < nCount; i++)
	{
		string oxarray = "";
		int sum = 0;
		int repcnt = 0;
		getline(cin, oxarray);
		for (size_t j = 0; j < oxarray.length(); j++)
		{
			if (oxarray[j] == 'O')
			{
				sum = sum + (++repcnt);
			}
			else
			{
				repcnt = 0;
			}
		}
		cout << sum << endl;
	}
}


void Prob4344_AvgMightbe()
{
	//총 라인수
	int nCount1 = 0;
	cin >> nCount1;
	int arr[1000] = { 0, };

	for (int i = 0; i < nCount1; i++)
	{
		int nCount2 = 0;
		cin >> nCount2;
		int sum1 = 0;

		for (int j = 0; j < nCount2; j++)
		{
			cin >> arr[j];
			sum1 += arr[j];
		}

		float avg1 = ((float)sum1 / nCount2);
		int sum2 = 0;
		int nCount3 = 0;

		for (int k = 0; k < nCount2; k++)
		{
			if (arr[k] > avg1)
			{
				nCount3++;
			}
		}

		float avg2 = ((float)nCount3 / (float)nCount2) * 100;
		avg2 = round(avg2 * 1000);
		avg2 = avg2 / 1000;

		cout.precision(3);
		cout << fixed << avg2 << "%" << endl;
	}
}

int Prob4673_GetSelfNumber(int n)
{
	int sum = n;
	while (true)
	{
		if (n == 0) { break; }
		sum += n % 10;
		n = n / 10;
	}
	return sum;
}

void Prob4673_SelfNumber()
{
#define SELFNUMBER_SIZE 10001
	bool arr[SELFNUMBER_SIZE] = { false, };

	for (int i = 1; i < SELFNUMBER_SIZE; i++)
	{
		int selfnum = Prob4673_GetSelfNumber(i);

		//cout << "SelfNum : [" << i << "] = " << selfnum << endl;

		if (selfnum < SELFNUMBER_SIZE)
		{
			arr[selfnum] = true;
		}
	}

	for (int i = 1; i < SELFNUMBER_SIZE; i++)
	{
		if (arr[i] == false) { cout << i << endl; }
	}
}