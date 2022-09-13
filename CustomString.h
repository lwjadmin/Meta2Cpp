#pragma once

#include <iostream>


class CustomString {
public:
	CustomString(const char* str) : mSize(sizeof(str) + 1) {
		mChar = new char[mSize];
		memcpy(mChar, str, sizeof(char) * mSize);
	}

	CustomString(const CustomString& others) : mSize(others.mSize) {
		mChar = new char[mSize];
		memcpy(mChar, others.mChar, sizeof(char) * mSize);
	}


	void PrintString() const {
		std::cout << mChar << std::endl;
	}

	~CustomString() {
		delete[] mChar;
		mSize = 0;
	}
private:
	char* mChar;
	size_t mSize;
};