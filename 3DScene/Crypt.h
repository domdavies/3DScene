#pragma once

#include "SceneObject.h"

class Crypt : public SceneObject
{
public:
	Crypt(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Crypt();
	void Draw();
private:
	Vector3 pos;
	Material* cryptMat;
};