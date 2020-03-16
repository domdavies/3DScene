#pragma once
#include "SceneObject.h"
#include "3DScene.h"

class Character : public SceneObject
{
public:
	Character(Mesh* mesh, Texture2D* texture, float x, float y, float z, float rotateSpeed);
	~Character();

	void Update();
	void Draw();

	void SetPosition(Vector3 position);

	void TurnLeft();
	void TurnRight();
	void Walk();
	int GetHP() { return HP; };
	float GetYRotation() { return angle; };
	Vector3 GetPosition() { return _position; };
private:
	int HP;
	float angle;
	Vector3 _position;
	float speed;
	float move;

	void Animate();

	Material* LilithMat;
};

