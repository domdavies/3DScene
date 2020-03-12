#ifndef _GRAVESTONE_H
#define _GRAVESTONE_H

#include "Structures.h"
#include "SceneObject.h"

class GraveStone : public SceneObject
{
public:
	GraveStone(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~GraveStone();

	void Draw();
private:
	Vector3 pos;
	Material* graveStoneMat;
};
#endif // !_GRAVESTONE_H