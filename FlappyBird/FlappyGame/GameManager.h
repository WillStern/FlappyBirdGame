#pragma once
#include "../Engine/Engine.h"
#include "../Engine/Graphics/Sprite.h"

#include "Flapper.h"
#include "PipeManager.h"
#include "Background.h"


class GameManager {

public:
	enum class State {
		START,
		GAMEPLAY,
		GAMEOVER,
		COUNT
	};

public:
	GameManager();
	~GameManager();

	void Start();
	void UpdateScoreSprites(int currentScore);

private:
	void SetState(State state);

private:
	Engine * mEngine;
	Flapper* mFlapper;
	PipeManager* mPipeManager;

	Sprite mStartSprite;
	Sprite mGameoverSprite;

	Sprite mBackgroundSprite_b;
	Sprite mBackgroundSprite_m;
	Sprite mBackgroundSprite_f;

	Sprite score_ones;
	Sprite score_tens;

	Background background_back;
	Background background_front;

	State mState;

};