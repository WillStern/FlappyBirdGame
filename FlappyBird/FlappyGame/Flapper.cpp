#include "Flapper.h"

#include "../Engine/Engine.h"
#include "../Engine/Math/Rect.h"
#include "../Engine/IO/Keyboard.h"
#include "../Engine/IO/Mouse.h"

Flapper::Flapper() {
	flapForce = 300.0f;
	maxRot = 30.0f;
	minRot = -maxRot;
}

Flapper::Flapper(Sprite _sprite) : Flapper(){
	sprite = _sprite;
	Vector3 sizeOffset(0.7f, 0.75f, 1); //offsets the players hit-box to allow for more generous hit detection
	Rect boundingRect = Rect();
	boundingRect.SetSize(*sprite.GetSize() * *sprite.GetScale() * sizeOffset);
	rb.Initialize(0.8f, -15, sprite.GetPos(), sprite.GetRot(), sprite.GetScale(), sprite.GetSize(), boundingRect);
}

void Flapper::Update() {

	HandleInput();

	sprite.Update();
	rb.Update();

	float yVel = rb.GetVel().y;
	if (flapForce == 0){
		cout << "Error: Flapping will do nothing! Setting to 300" << endl;
		flapForce = 300.0f;
	}
	float newRot = yVel * (maxRot / flapForce);
	sprite.RotateTo(newRot);
}

void Flapper::Render() {
	sprite.Render();
	//rb.Render(Vector3(0, 0, 0)); // Comment in to render the flapper's hit-box
}

void Flapper::Flap() {
	rb.SetVel(Vector3(0, flapForce, 0));
	sprite.RotateTo(maxRot);
}

Sprite& Flapper::GetSprite() {
	return sprite;
}

Rigidbody& Flapper::GetRB() {
	return rb;
}

void Flapper::Reset() {
	sprite.MoveTo(Vector3((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0));
	sprite.RotateTo(0);
	rb.SetVel(Vector3(0));
}

//private

void Flapper::HandleInput() {
	if (Keyboard::KeyDown(GLFW_KEY_SPACE) || Mouse::ButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
		Flap();
	}
}