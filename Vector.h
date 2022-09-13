#pragma once

#include <iostream>

namespace Vector {
	class Vector2D {
	public:
		Vector2D() : mX(0), mY(0) { }
		Vector2D(int mX, int mY) : mX(mX), mY(mY) {}
		Vector2D(const Vector2D& others) : mX(others.mX), mY(others.mY) {
			//this->mX = others.mX;
			//this->mY = others.mY;
		}

		int GetX() const { return mX; }
		int GetY() const { return mY; }
		void SetXY(const int x, const int y) 
		{
			mX = x;
			mY = y;
		}
		void Add(const Vector2D& others) {
			this->mX += others.mX;
			this->mY += others.mY;
		}
		void Mul(const Vector2D& others) {
			this->mX *= others.mX;
			this->mY *= others.mY;
		}

		Vector2D operator+(const Vector2D& other) {
			Vector2D sum;
			sum.mX += other.mX;
			sum.mY += other.mY;
			return sum;
		}
		Vector2D operator*(const Vector2D& other) {
			Vector2D mul;
			mul.mX *= other.mX;
			mul.mY *= other.mY;
			return mul;
		}
		Vector2D operator*(const float other) {
			Vector2D mul;
			mul.mX *= other;
			mul.mY *= other;
			return mul;
		}


		void PrintVector() {
			std::cout << "X : " << mX << ",Y : " << mY << std::endl;
		}
	private:
		int mX;
		int mY;
	};


	void Run() {
		//Stack
		Vector2D vListStack[10];
		memset(vListStack, 0, sizeof(Vector2D) * 10);

		//Heap
		Vector2D* vListHeap = new Vector2D[10];
		delete[] vListHeap;

		int* iarr = (int*)malloc(sizeof(int) * 10);
		if (iarr != NULL) {
			//MemAlloc Success
			memset(iarr, 0, sizeof(int) * 10);
			free(iarr);
		}

		
		
	}
}