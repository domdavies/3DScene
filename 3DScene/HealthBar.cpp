#include "HealthBar.h"

HealthBar::HealthBar(Texture2D* texture) : HUDTextures(texture)
{
	HP = 200;
}

void HealthBar::Update()
{
	HP -= .1;

	if (HP <= 10)
	{
		HP = 10; //10 is the starting pos of the healthbar texture... so therefore no life
		//player is dead;
	}
}

void HealthBar::Draw() {
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(10, 5);
	glTexCoord2f(1, 0);
	glVertex2f(HP, 5);
	glTexCoord2f(1, 1);
	glVertex2f(HP, 15);
	glTexCoord2f(0, 1);
	glVertex2f(10, 15);
	glEnd();
}