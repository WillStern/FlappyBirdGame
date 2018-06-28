#pragma once
#include "Pipe.h"
#include "../Engine/Math/Rect.h"
#include "../Engine/Math/Math.h"
#include "../Engine/Engine.h"


class Background {

public:

	Background();
	Background(Sprite _backSprite, Sprite _midSprite);
	Background(Sprite _frontSprite);

	void Update();
	void Render();

	void SetSpeed(float _speed);

	void UpdateSprites();
	void Reset();

private:
	Sprite backSprite;
	Sprite midSprite;
	Sprite frontSprite;	
	
	Sprite backSprite_copy;
	Sprite midSprite_copy;
	Sprite frontSprite_copy;

	Vector3 pos;

	float speed;
	float parralaxOffset;

	bool isForeground;
};