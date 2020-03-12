#pragma once
#include "Structures.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

namespace OBJMeshLoader
{
	Mesh* LoadOBJ(char* path);
};