#pragma once
#include "../Math/Vector3.h"
#include "../Math/Rect.h"

class Rigidbody {
public:

	static bool IsColliding(const Rigidbody& rbA, const Rigidbody& rbB);

	Rigidbody();
	
	void Initialize(float _friction, float _gravity, Vector3* _pos, float* _rot, Vector3* _scale, Vector3* _size, Rect _boundingRect);
	void Update();
	void Render(Vector3 c); //mainly for debugging, this vector3 is a color

	void AddForce(Vector3 force);

	Vector3 GetVel();
	void SetVel(Vector3 _vel);

private:
	Vector3* pos;
	float* rot;
	float lastRot;
	Vector3* scale;
	Vector3* size;

	float gravity;
	float friction;
	Vector3 vel; //velocity vector

	Rect boundingRect;
};