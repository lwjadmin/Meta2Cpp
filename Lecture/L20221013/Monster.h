#pragma once
#include "Actor.h"

class AMonster : public AActor
{
public:
	AMonster();
	AMonster(int NewX, int NewY);
	~AMonster();

	virtual void Tick() override;
	bool PredictCanMove();
	virtual bool CheckHit(AActor* Other) override;
	Uint64 ElapsedTime = 0;
	Uint64 ExecuteTime = 0;
	bool bTouched;
};