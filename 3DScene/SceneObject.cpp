#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture) {
	_mesh = mesh;
	_texture = texture;
}

SceneObject::~SceneObject() {

}

void SceneObject::Update() {

}

void SceneObject::Draw() {

}

void SceneObject::SetPosition(Vector3 position) {

}

void SceneObject::TurnLeft() {

}

void SceneObject::TurnRight() {

}

void SceneObject::Walk() {

}

int SceneObject::GetHP()
{
	return 0;
}