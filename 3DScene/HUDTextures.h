#pragma once
#include "Texture2D.h"

class HUDTextures
{
public:
	HUDTextures(Texture2D* texture);

	virtual void Update();
	virtual void Draw();
protected:
	Texture2D* _texture;
};