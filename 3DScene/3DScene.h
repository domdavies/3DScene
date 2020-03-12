#pragma once
#define REFRESHRATE 16
#define M_PI 3.14159265358979323846264338327950288
#include "Structures.h"
#include "GLUTCallBacks.h"
#include <Windows.h>
#include "GL/freeglut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include "objLoader.h"
#include "MeshLoader.h"
#include "Character.h"
#include "GraveStone.h"
#include "Crypt.h"
#include "BackGroundHealthBar.h"
#include "HealthBar.h"
#include "HUDTextures.h"

class OBJLoader;

class HelloGL
{
public:
	//constructor
	HelloGL(int argc, char* argv[]);
	void InitObjects();
	void InitLighting();
	void InitGL(int argc, char* argv[]);
	//destructor
	~HelloGL(void);
	//function used to display grapghics
	void Display();
	void Update();
	void ResetMat();
	void DrawString(const char* text, Vector3* position, Color* color);

	void MouseMove(int x, int y);
	void MouseButton(int button, int state, int x, int y);
	void Keyboard(unsigned char key, int x, int y);
	void SpecialKeys(int key, int x, int y);
private:
	float rotation;
	float xRot, zRot, yRot;
	Camera* camera;
	SceneObject* crypt;
	SceneObject* lilith;
	SceneObject* graveStone[10][10];
	Vector4* _lightPosition;
	Lighting* _lightData;
	Material* defaultMat;
	HUDTextures* healthBar;
	HUDTextures* backGroundHealthBar;

	//static Vertex indexVertices[];
	//static Vertex indexedColors[];
	//static GLushort indices[];

	float deltaAngle;
	int xOrigin;
	float angle;
	float move;
	float moveCharacter;
	float dist;
};