#pragma once

#include "Texture2D.h"
#include "HUDTextures.h"

class BackGroundHealthBar : public HUDTextures
{
public:
	BackGroundHealthBar(Texture2D* texture);

	void Draw();
private:

};