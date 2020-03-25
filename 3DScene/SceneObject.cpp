#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture) {
	_mesh = mesh;
	_texture = texture;
	parent = NULL;
}

SceneObject::~SceneObject() {
	for (int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
}

void SceneObject::Update() {
	for (std::vector<SceneObject*>::iterator i = children.begin(); i != children.end();  ++i)
	{
		(*i)->Update();
	}
}

void SceneObject::Draw() {
}

void SceneObject::AddChild(SceneObject* s)
{
	children.push_back(s);
	s->parent = this;
}
