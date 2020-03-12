#include "Character.h"
#include <math.h>

Character::Character(Mesh* mesh, Texture2D* texture, float x, float y, float z, float rotateSpeed) : SceneObject(mesh, texture) {
	angle = 0;
	move = 0;
	speed = rotateSpeed;

	HP = 200;

	_position.x = x;
	_position.y = y;
	_position.z = z;
}

Character::~Character() {

}

void Character::SetPosition(Vector3 position) {
	_position.x = position.x;
	_position.y = position.y;
	_position.z = position.z;
}

void Character::Update() {
	//angle += 1;
}

void Character::Animate() {

}

void Character::TurnLeft() {
	angle += 1;
}

void Character::TurnRight() {
	angle -= 1;
}

void Character::Walk() {
	move += .02;

	float mx = move * sin((angle * M_PI / 180));
	float mz = move * cos(angle * M_PI / 180);
	_position.x += mx;
	_position.z += mz;
}

void Character::Draw() {
	LilithMat = new Material();
	LilithMat->ambient.x = 0.8;
	LilithMat->ambient.y = 0.2;
	LilithMat->ambient.z = 0.2;
	LilithMat->ambient.w = 1.0;

	LilithMat->diffuse.x - 0.0;
	LilithMat->diffuse.y = 0.0;
	LilithMat->diffuse.z = 0.0;
	LilithMat->diffuse.w = 1.0;

	LilithMat->specular.x = 0.0;
	LilithMat->specular.y = 0.0;
	LilithMat->specular.z = 0.0;
	LilithMat->specular.w = 1.0;

	LilithMat->shininess = 20.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(LilithMat->ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(LilithMat->diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(LilithMat->specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, LilithMat->shininess);

	//glBindTexture(GL_TEXTURE_2D, _texture->GetID());

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(angle, 0, 1, 0);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < _mesh->out_vertices.size(); i++)
	{
		//glTexCoord2fv(&_mesh->out_textures[i].u);
		glNormal3fv(&_mesh->out_normals[i].x);
		glVertex3fv(&_mesh->out_vertices[i].x);
	}
	glEnd();
	glPopMatrix();
}