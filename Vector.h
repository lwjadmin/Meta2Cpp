#pragma once

#include <iostream>

namespace Vector {
	class Vector2D {
	public:
		Vector2D() : mX(0), mY(0) { }
		Vector2D(int mX, int mY) : mX(mX), mY(mY) {}
		const int GetX() { return mX; }
		const int GetY() { return mY; }
		void SetXY(const int x, const int y) 
		{
			mX = x;
			mY = y;
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
	}
}