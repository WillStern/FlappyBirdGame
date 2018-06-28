#include "Background.h"
#include "../Engine/Math/Vector3.h"


Background::Background() {
	speed = 150.0f;
	parralaxOffset = 1.0f / 5.0f;
}

Background::Background(Sprite _backSprite, Sprite _midSprite) : Background() {
	backSprite	= _backSprite;
	midSprite	= _midSprite;
	frontSprite;
	backSprite_copy = backSprite;
	midSprite_copy = midSprite;
	frontSprite_copy;

	backSprite_copy.MoveTo(Vector3(	(float)Engine::SCREEN_WIDTH*2, (float)Engine::SCREEN_HEIGHT/2, 0));
	midSprite_copy.MoveTo(Vector3(	(float)Engine::SCREEN_WIDTH*2, (float)Engine::SCREEN_HEIGHT/2, 0));


	isForeground = false;
}

Background::Background(Sprite _frontSprite) : Background() {
	backSprite;
	midSprite;
	backSprite_copy;
	midSprite_copy;
	frontSprite = _frontSprite;
	frontSprite_copy = frontSprite;

	frontSprite_copy.MoveTo(Vector3((float)Engine::SCREEN_WIDTH*2, (float)Engine::SCREEN_HEIGHT / 2, 0));

	isForeground = true;
}

void Background::Update() {
	backSprite.MoveBy(Vector3(		(-speed * parralaxOffset) / 2.0f, 0.0f, 0.0f));
	midSprite.MoveBy(Vector3(		(-speed * parralaxOffset), 0.0f, 0.0f));
	frontSprite.MoveBy(Vector3(		-speed, 0.0f, 0.0f));
	backSprite_copy.MoveBy(Vector3(	(-speed * parralaxOffset) / 2.0f, 0.0f, 0.0f));
	midSprite_copy.MoveBy(Vector3(	(-speed * parralaxOffset), 0.0f, 0.0f));
	frontSprite_copy.MoveBy(Vector3(-speed, 0.0f, 0.0f));

	UpdateSprites();

}

void Background::Render() {
	if (isForeground) {
		frontSprite.Render();
		frontSprite_copy.Render();
	}
	else {
		backSprite.Render();
		backSprite_copy.Render();
		midSprite.Render();
		midSprite_copy.Render();
	}
}

void Background::SetSpeed(float _speed) {
	speed = _speed;
}

//needs to be updated to adjust background based on the sizes of the images not arbitrary numbers
void Background::UpdateSprites() {

	if (backSprite.GetPos()->x < -775)
		backSprite.MoveTo(Vector3(		(float)Engine::SCREEN_WIDTH * 2, (float)Engine::SCREEN_HEIGHT / 2, 0));

	if (midSprite.GetPos()->x < -775)
		midSprite.MoveTo(Vector3(		(float)Engine::SCREEN_WIDTH * 2, (float)Engine::SCREEN_HEIGHT / 2, 0));

	if (frontSprite.GetPos()->x < -775)
		frontSprite.MoveTo(Vector3(		(float)Engine::SCREEN_WIDTH * 2, (float)Engine::SCREEN_HEIGHT / 2, 0));

	if (backSprite_copy.GetPos()->x < -775)
		backSprite_copy.MoveTo(Vector3(	(float)Engine::SCREEN_WIDTH * 2, (float)Engine::SCREEN_HEIGHT / 2, 0));

	if (midSprite_copy.GetPos()->x < -775)
		midSprite_copy.MoveTo(Vector3(	(float)Engine::SCREEN_WIDTH * 2, (float)Engine::SCREEN_HEIGHT / 2, 0));

	if (frontSprite_copy.GetPos()->x < -775)
		frontSprite_copy.MoveTo(Vector3((float)Engine::SCREEN_WIDTH * 2, (float)Engine::SCREEN_HEIGHT / 2, 0));

}

void Background::Reset() {
	backSprite.MoveTo(Vector3(		(float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0.0f));
	midSprite.MoveTo(Vector3(		(float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0.0f));
	frontSprite.MoveTo(Vector3(		(float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0.0f));
	backSprite_copy.MoveTo(Vector3(	(float)Engine::SCREEN_WIDTH*2, (float)Engine::SCREEN_HEIGHT / 2, 0.0f));
	midSprite_copy.MoveTo(Vector3(	(float)Engine::SCREEN_WIDTH*2, (float)Engine::SCREEN_HEIGHT / 2, 0.0f));
	frontSprite_copy.MoveTo(Vector3((float)Engine::SCREEN_WIDTH*2, (float)Engine::SCREEN_HEIGHT / 2, 0.0f));
}