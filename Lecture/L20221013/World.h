#pragma once
#include <vector>

#include <string>

using namespace std;

class AActor;

class FWorld
{
public:
	FWorld();
	~FWorld();
	vector<AActor*> ActorList;
	void SpawnActor(AActor* NewActor);
	void DestroyActor(AActor* DeleteActor);
	void Render();
	void Tick(); 
	void BeginPlay();
	void EndPlay();
	void Terminate();
	bool bTerminateCalled;
};

