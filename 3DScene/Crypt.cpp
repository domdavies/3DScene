#include "Crypt.h"

Crypt::Crypt(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture) {
	pos.x = x;
	pos.y = y;
	pos.z = z;
}


Crypt::~Crypt() {

}

void Crypt::Draw() {
	/*
	cryptMat = new Material();
	cryptMat->ambient.x = .2f;
	cryptMat->ambient.y = .5f;
	cryptMat->ambient.z = .8f;
	cryptMat->ambient.w = 1.0f;

	cryptMat->diffuse.x - .4f;
	cryptMat->diffuse.y = .4f;
	cryptMat->diffuse.z = .4f;
	cryptMat->diffuse.w = 1.0f;

	cryptMat->specular.x = .5f;
	cryptMat->specular.y = .7f;
	cryptMat->specular.z = .3f;
	cryptMat->specular.w = 1.0f;

	cryptMat->shininess = 100.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(cryptMat->ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(cryptMat->diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(cryptMat->specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, cryptMat->shininess);
	*/

	glBindTexture(GL_TEXTURE_2D, _texture->GetID());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glPushMatrix();
	glScalef(1, 1, 1);
	glTranslatef(pos.x, pos.y, pos.z);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < _mesh->out_vertices.size(); i++)
	{
		glTexCoord2fv(&_mesh->out_textures[i].u);
		glNormal3fv(&_mesh->out_normals[i].x);
		glVertex3fv(&_mesh->out_vertices[i].x);
	}
	glEnd();
	glPopMatrix();
}
