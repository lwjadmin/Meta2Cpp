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
	void DestroyAllActors();
	void DestroyActor(AActor* DeleteActor);
	void Render();
	void Tick(); 
	void Load(string MapFileName);
};

