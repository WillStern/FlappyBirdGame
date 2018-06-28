#include "Pipe.h"
#include "../Engine/Math/Rect.h"
#include "../Engine/Math/Math.h"
#include "../Engine/Engine.h"

Sprite* Pipe::pipeSprite = NULL;

void Pipe::Initialize() {
	pipeSprite = new Sprite("Assets/Art/pipe.png");
	pipeSprite->SetScale(1);
}

Pipe::Pipe() {
	if (!pipeSprite) {
		cout << "Error: Tried to instantiate a Pipe without calling Initialize method!" << endl;
		return;
	}

	topSprite = Sprite(*pipeSprite);
	botSprite = Sprite(*pipeSprite);

	gap = 200;
	speed = 250;
}

Pipe::Pipe(Vector3 _pos) : Pipe() {
	if (!pipeSprite) {
		return;
	}

	pos = _pos + Vector3(GetWidth(), 0, 0);
	prevPos = pos.x;

	UpdatePos();
	topSprite.SetScale(*topSprite.GetScale() * Vector3(1, -1, 1)); // flips the image

	Rect topRC = Rect();
	topRC.SetSize(Vector3(Math::Abs(topSprite.GetSize()->x * topSprite.GetScale()->x) * 0.7f, Math::Abs(topSprite.GetSize()->y * topSprite.GetScale()->y) * 0.95f, 1));
	topRB = Rigidbody();
	topRB.Initialize(1, 0, topSprite.GetPos(), topSprite.GetRot(), topSprite.GetScale(), topSprite.GetSize(), topRC);

	Rect botRC = Rect();
	botRC.SetSize(Vector3(Math::Abs(botSprite.GetSize()->x * botSprite.GetScale()->x) * 0.7f, Math::Abs(botSprite.GetSize()->y * botSprite.GetScale()->y) * 0.95f, 1));
	botRB = Rigidbody();
	botRB.Initialize(1, 0, botSprite.GetPos(), botSprite.GetRot(), botSprite.GetScale(), botSprite.GetSize(), botRC);

	topRB.AddForce(Vector3(-speed, 0, 0));
	botRB.AddForce(Vector3(-speed, 0, 0));
}

void Pipe::SetGap(float _gap) {
	gap = _gap;
	UpdatePos();
}

float Pipe::GetPrevPos() {
	return prevPos;
}

void Pipe::IncreaseSpeed(float _speed) {
	topRB.AddForce(Vector3(-_speed, 0, 0));
	botRB.AddForce(Vector3(-_speed, 0, 0));
	UpdatePos();
}

void Pipe::Update() {
	prevPos = topSprite.GetPos()->x;
	topRB.Update();
	botRB.Update();
}

void Pipe::Render() {
	topSprite.Render();
	botSprite.Render();
	//topRB.Render(Vector3(1, 0, 0)); //comment these in to view the pipes' hit-boxes
	//botRB.Render(Vector3(1, 0, 0));
}

void Pipe::MoveTo(Vector3 to) {
	pos = to;
	UpdatePos();
}

void Pipe::MoveBy(Vector3 by) {
	pos = pos + by;
	UpdatePos();
}

float Pipe::GetX() {
	return topSprite.GetPos()->x;
}

float Pipe::GetWidth() {
	return topSprite.GetSize()->x * topSprite.GetScale()->x;
}

void Pipe::UpdatePos() {
	Vector3 topPos = pos;
	topPos.y += (gap / 2) + Math::Abs(topSprite.GetSize()->y * topSprite.GetScale()->y / 2);
	topSprite.MoveTo(topPos);

	Vector3 botPos = pos;
	botPos.y -= (gap / 2) + Math::Abs(botSprite.GetSize()->y * botSprite.GetScale()->y / 2);
	botSprite.MoveTo(botPos);
}

Rigidbody Pipe::GetTopRB() {
	return topRB;
}

Rigidbody Pipe::GetBotRB() {
	return botRB;
}