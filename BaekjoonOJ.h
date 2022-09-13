#pragma once
#include <iostream>
#include <string>
using namespace std;

void Prob2557() {
	std::cout << "Hello World!" << std::endl;
}

void Prob10718() {
	std::cout << "����ģ�� ��������" << std::endl;
	std::cout << "����ģ�� ��������" << std::endl;
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
	//double���� ���е� : 12
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
	ü�� : 16�� �ǽ�, ŷ1, ��1, ��2, ���2, ����Ʈ2, ��8
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