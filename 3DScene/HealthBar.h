#pragma once
#include "HUDTextures.h"

class HealthBar : public HUDTextures
{
public:
	HealthBar(Texture2D* texture);

	void Update();
	void Draw();
private:
	int HP;
};