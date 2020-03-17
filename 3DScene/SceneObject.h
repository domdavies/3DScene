#pragma once
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh* _mesh;
	Texture2D* _texture;
public:
	SceneObject(Mesh* mesh, Texture2D* texture);

	virtual ~SceneObject();
	virtual void Update();
	virtual void Draw();
	virtual void SetPosition(Vector3 position);
	virtual void TurnLeft();
	virtual void TurnRight();
	virtual void Walk();
	virtual int GetHP();
	virtual float GetYRotation(){ return 0; };
	virtual Vector3 GetPosition() { return {0, 50, 50 }; };
private:
};

