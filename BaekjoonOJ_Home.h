#pragma once
#include <iostream>

using namespace std;

void Prob10430_PrintAll() {
	int A = 0;
	int B = 0;
	int C = 0;

	cin >> A >> B >> C;
	cout << (A + B) % C << endl;
	cout << ((A % C) + (B % C)) % C << endl;
	cout << (A * B) % C << endl;
	cout << ((A % C) * (B % C)) % C << endl;
}

void Prob2588_Adder() {
	int number1 = 0;
	int number2 = 0;

	cin >> number1;
	cin >> number2;

	int num1 = number2 % 10;
	int num10 = (number2 % 100) / 10;
	int num100 = (number2 % 1000) / 100;

	int total = 0;

	cout << number1 * num1 << endl;
	cout << number1 * num10 << endl;
	cout << number1 * num100 << endl;
	cout << (number1 * num1) + (number1 * num10 * 10) + (number1 * num100 * 100) << endl;
}

void Prob2588_PrintCat() {
	cout << "\\    /\\" << endl;
	cout << " )  ( ')" << endl;
	cout << "(  /  )" << endl;
	cout << " \\(__)|" << endl;
}

void Prob10172_PrintDog() {
	cout << "|\\_/|" << endl;
	cout << "|q p|   /}" << endl;
	cout << "( 0 )\"\"\"\\" << endl;
	cout << "|\"^\"`    |" << endl;
	cout << "||_/=\\\\__|" << endl;
}

void Prob25083_PrintLeaf() {
	cout << "         ,r'\"7" << endl;
	cout << "r`-_   ,'  ,/" << endl;
	cout << " \\. \". L_r'" << endl;
	cout << "   `~\\/" << endl;
	cout << "      |" << endl;
	cout << "      |" << endl;
}

void Prob1330_Compare() {
	int a = 0;
	int b = 0;
	cin >> a >> b;
	if (a == b) {
		cout << "==";
	}
	else if (a > b) {
		cout << ">";
	}
	else if (a < b) {
		cout << "<";
	}
}

void Proj9498_GetScore() {
	int scores = 0;
	cin >> scores;
	if (scores >= 90 && scores <= 100) {
		cout << "A";
	}
	else if (scores >= 80) {
		cout << "B";
	}
	else if (scores >= 70) {
		cout << "C";
	}
	else if (scores >= 60) {
		cout << "D";
	}
	else {
		cout << "F";
	}
}

void Prob2753_PrintLeapYear() {
	int year = 0;
	cin >> year;
	bool condition1 = (year % 4 == 0) ? true : false;
	bool condition2 = (year % 100 != 0) ? true : false;
	bool condition3 = (year % 400 == 0) ? true : false;

	if ((condition1 && condition2) || condition3) {
		cout << "1";
	}
	else {
		cout << "0";
	}
}

void Prob2753_CheckQuadrant() {
	int x;
	int y;
	cin >> x;
	cin >> y;

	if (x > 0 && y > 0) {
		cout << 1;
	}
	else if (x > 0 && y < 0) {
		cout << 4;
	}
	else if (x < 0 && y > 0) {
		cout << 2;
	}
	else if (x < 0 && y < 0) {
		cout << 3;
	}

}


void Prob2884_EarlyAlarm() {
	int hours = 0;
	int minutes = 0;
	int totalMinutes = 0;
	cin >> hours >> minutes;
	totalMinutes = (hours * 60) + minutes;

	if ((totalMinutes - 45) >= 0) {
		totalMinutes -= 45;
	}
	else {
		totalMinutes -= 45;
		totalMinutes += (60 * 24);
	}

	hours = totalMinutes / 60;
	minutes = totalMinutes % 60;
	cout << hours << " " << minutes;

}

void Prob2525_OvenWatch() {
	int hours = 0;
	int minutes = 0;
	int setminutes = 0;
	int totalMinutes = 0;
	cin >> hours >> minutes;
	cin >> setminutes;

	totalMinutes = (hours * 60) + minutes + setminutes;
	if (totalMinutes >= (24 * 60)) {
		totalMinutes -= (24 * 60);
	}


	cout << totalMinutes / 60 << " " << totalMinutes % 60 << endl;

}