#pragma once

#ifndef __AACTOR_H__
#define __AACTOR_H__ 


class AActor
{
public:
	AActor();
	virtual ~AActor();

	virtual void Draw();
	virtual void Tick();
	virtual void Move(int NewX, int NewY);
	int X;
	int Y;

	char Shape;
};

#endif


