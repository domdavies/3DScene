#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include <fstream>
#include <iostream>

using namespace std;

class Texture2D
{
private:
	GLuint _ID;
	int _width, _height;
public:
	Texture2D();
	~Texture2D();

	bool LoadRAW(char* path, int width, int height);
	bool LoadBMP(char* path);
	GLuint GetID() const { return _ID; };
	int GetWidth() const { return _width; };
	int GetHeight() const { return _height; };
};
#endif _TEXTURE2D_H