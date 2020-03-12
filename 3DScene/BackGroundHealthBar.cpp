#include "BackGroundHealthBar.h"

BackGroundHealthBar::BackGroundHealthBar(Texture2D* texture) : HUDTextures(texture)
{

}

void BackGroundHealthBar::Draw() {
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(7, 2);
	glTexCoord2f(1, 0);
	glVertex2f(210, 2);
	glTexCoord2f(1, 1);
	glVertex2f(210, 18);
	glTexCoord2f(0, 1);
	glVertex2f(7, 18);
	glEnd();
}