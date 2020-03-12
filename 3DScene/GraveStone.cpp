#include "GraveStone.h"

GraveStone::GraveStone(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture) {
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

GraveStone::~GraveStone() {

}

void GraveStone::Draw() {
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glPushMatrix();
	glScalef(3, 3, 3);
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