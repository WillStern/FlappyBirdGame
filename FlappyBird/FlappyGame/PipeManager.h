#pragma once

#include "Pipe.h"
#include "Flapper.h"

#include <vector>
using namespace std;

class PipeManager {

public:
	PipeManager();
	~PipeManager();

	void Update();
	void Render();

	bool CheckCollision(Flapper& flapper);

	void Reset();

	float GetPipeSpeed();
	int GetScore();

private:
	void CreatePipe();

private:
	vector<Pipe*> pipes;

	float xStartSeparation;
	float yStartSeparation;
	float xSeparation; // separation between pipes
	float minXSeparation;
	float ySeparation; // handles gap between pipes
	float minYSeparation;
	float xSeparationSpeed;
	float ySeparationSpeed;

	float pipeSpeedIncrease;
	float currentPipeSpeed;

	int minSpawnY;
	int maxSpawnY;

	int totalPipes;
	int points;
};