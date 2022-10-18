#pragma once
#include "Actor.h"

class AGoal : public AActor
{
public:
	AGoal();
	AGoal(int NewX, int NewY);
	~AGoal();
	bool isComplete;
	Uint64 ElapsedTime = 0;
	Uint64 ExecuteTime = 0;
	virtual void Tick() override;
};