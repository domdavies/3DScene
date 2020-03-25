#pragma once
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh* _mesh;
	Texture2D* _texture;
public:
	SceneObject(Mesh* mesh = NULL, Texture2D* texture = NULL);

	virtual ~SceneObject();
	virtual void Update();
	virtual void Draw();

	void AddChild(SceneObject* s);
	std::vector<SceneObject*>::const_iterator GetChildIteratotStart() { return children.begin(); };
	std::vector<SceneObject*>::const_iterator GetChildIteratotEnd() { return children.end(); };
private:
	SceneObject* parent;
	Mesh* mesh;
	std::vector<SceneObject*> children;
};

