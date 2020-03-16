#include "3DScene.h"
#include <iostream>

using namespace::std;

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitLighting();
	InitObjects();
	glutMainLoop();
}

void HelloGL::InitObjects() {
	camera = new Camera();

	/*
	----------------------------------------------------------------------
						LOAD MESH DATA FROM FILES
	----------------------------------------------------------------------
	*/
	//Mesh* CubeMesh = MeshLoader::Load((char*)"cube.txt");
	Mesh* lilithMesh = OBJMeshLoader::LoadOBJ((char*)"lilith_model.obj");
	Mesh* graveStoneMesh = OBJMeshLoader::LoadOBJ((char*)"Gravestone.obj");
	Mesh* cryptMesh = OBJMeshLoader::LoadOBJ((char*)"Crypt.obj");
	/*
	----------------------------------------------------------------------
	----------------------------------------------------------------------
	*/

	/*
	----------------------------------------------------------------------
					  LOAD TEXTURE DATA FROM FILES
	----------------------------------------------------------------------
	*/

	Texture2D* texture = new Texture2D();
	texture->LoadRAW((char*)"Penguins.raw", 512, 512);

	Texture2D* bmptex = new Texture2D();
	bmptex->LoadBMP((char*)"Gravestone.bmp");

	Texture2D* CryptTex = new Texture2D();
	CryptTex->LoadBMP((char*)"GraveYard_Crypt.bmp");

	Texture2D* HealthBarTex = new Texture2D();
	HealthBarTex->LoadBMP((char*)"HealthBar.bmp");

	Texture2D* backGroundHPTex = new Texture2D();
	backGroundHPTex->LoadBMP((char*)"BackGroundHealthBar.bmp");
	/*
	----------------------------------------------------------------------
	----------------------------------------------------------------------
	*/

	//store data for lilith character
	lilith = new Character(lilithMesh, nullptr, 0, 50, 50, 0);

	//store data for creating gravestones
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			graveStone[i][j] = new GraveStone(graveStoneMesh, bmptex, j * 6, 0, i * 3);
		}
	}

	crypt = new Crypt(cryptMesh, CryptTex, 3, 5, -15);

	healthBar = new HealthBar(HealthBarTex);

	backGroundHealthBar = new BackGroundHealthBar(backGroundHPTex);
	/*
	--------------------------------------------------------------------------------
									CAMERA DATA
	--------------------------------------------------------------------------------
	*/
	//x, y, z position
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 0.0f;
	//x, y, z lookat
	camera->centre.x = 0.0f; camera->centre.y = 0.0f; camera->centre.z = 0.0f;
	//x, y, z rotation
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	/*
	--------------------------------------------------------------------------------
	--------------------------------------------------------------------------------
	*/
	deltaAngle = 0.0f;
	xOrigin = -1;
	angle = 0.0f;

	move = 0;
	camDistanceFromPlayer = 20.0f;
}

void HelloGL::InitLighting() {
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->ambient.x = 0.2f;
	_lightData->ambient.y = 0.2f;
	_lightData->ambient.z = 0.2f;
	_lightData->ambient.w = 1.0;

	_lightData->diffuse.x - 0.8f;
	_lightData->diffuse.y = 0.8f;
	_lightData->diffuse.z = 0.8f;
	_lightData->diffuse.w = 1.0f;

	_lightData->specular.x = 0.2f;
	_lightData->specular.y = 0.2f;
	_lightData->specular.z = 0.2f;
	_lightData->specular.w = 1.0f;
}

void HelloGL::InitGL(int argc, char* argv[]) {
	GLUTCallBacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow("S!mple OpenGL window");
	/*
	--------------------------------------------------------------------------------------------
	CALLBACK FUNTIONS
	--------------------------------------------------------------------------------------------
	*/
	glutDisplayFunc(GLUTCallBacks::Display);
	glutKeyboardFunc(GLUTCallBacks::Keyboard);
	glutMouseFunc(GLUTCallBacks::MouseButton);
	glutMotionFunc(GLUTCallBacks::MouseMove);
	glutSpecialFunc(GLUTCallBacks::SpecialKeys);
	//16 is used because we want 60fps.
	//1000ms in a second. so 1000/60 which gives 16.6666, but we have to round to a whole number
	glutTimerFunc(REFRESHRATE, GLUTCallBacks::Timer, REFRESHRATE);
	/*
	--------------------------------------------------------------------------------------------
	END CALLBACKS
	--------------------------------------------------------------------------------------------
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//sets the viewport to be the screen size
	glViewport(0, 0, 800, 800);
	//set the correct perspective
	//FOV, aspect ratio, near clipping and far clipping
	gluPerspective(45, 1, 1, 1000);
	//switch back to modelview matrix to work with models
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_NORMAL_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//enable backface culling to view 3D objects
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE); //temporary, need to make sure triangles are drawn in the correct winding order
}

HelloGL::~HelloGL(void)
{
	delete camera;
}

void HelloGL::CalculateCamPos(float vertDist, float horiDis) {
	float theta = lilith->GetYRotation();
	float offsetX = horiDis * sin(theta * M_PI / 180);
	float offsetZ = horiDis * cos(theta * M_PI / 180);

	cout << theta << endl;

	camera->eye.x = lilith->GetPosition().x - offsetX;
	camera->eye.y = lilith->GetPosition().y + vertDist;
	camera->eye.z = lilith->GetPosition().z - offsetZ;

	cout << "Lil: " << lilith->GetPosition().z << endl;
	cout << "Cam: " << camera->eye.z << endl;
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->centre.x, camera->centre.y, camera->centre.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	lilith->Update();
	healthBar->Update();
	float vertDist = CalculatVericalDistance();
	float horDist = CalculateHorizontalDistance();
	//10, 16
	CalculateCamPos(vertDist, horDist);
}

void HelloGL::SpecialKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		//move -= 0.01;
		//camera->eye.x += .1 * sin(move);
		//camera->eye.z += .1 * cos(move);
		break;
	case GLUT_KEY_RIGHT:
		//move += 0.01;
		//camera->eye.x += .1 * sin(move);
		//camera->eye.z += .1 * cos(move);
		//cout << camera->eye.x << " " << camera->eye.z << endl;
		break;
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	}
}

void HelloGL::MouseMove(int x, int y) {

}

void HelloGL::MouseButton(int button, int state, int x, int y) {
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
		//3 designates the middle mouse scroll forward
	case 3:
		//camera->eye.z -= 0.2f;
		break;
		//4 designates the middle mouse scroll backwards
	case 4:
		//camera->eye.z += 0.2f;
		break;
	}
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
	{
		lilith->TurnRight();
	}
	if (key == 'a')
	{
		lilith->TurnLeft();
	}

	if (key == 'w')
	{
		lilith->Walk();
	}

	if (key == 's')
	{

	}

	if (key == ' ')
	{

	}
}

void HelloGL::ResetMat() {
	defaultMat = new Material();

	defaultMat->ambient.x = 1;
	defaultMat->ambient.y = 1;
	defaultMat->ambient.z = 1;
	defaultMat->ambient.w = 1.0;

	defaultMat->diffuse.x - 1;
	defaultMat->diffuse.y = 1;
	defaultMat->diffuse.z = 1;
	defaultMat->diffuse.w = 1.0;

	defaultMat->specular.x = 1;
	defaultMat->specular.y = 1;
	defaultMat->specular.z = 1;
	defaultMat->specular.w = 1.0;

	defaultMat->shininess = 0.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(defaultMat->ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(defaultMat->diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(defaultMat->specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, defaultMat->shininess);
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	//font as first paramater
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears the scene
	/*
	------------------------------------------------------------------------
	------------------------------------------------------------------------
				Set up 3d scene using the model matrix
	------------------------------------------------------------------------
	------------------------------------------------------------------------
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, 1, 1, 1000);
	glMatrixMode(GL_MODELVIEW);

	lilith->Draw();
	ResetMat();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			graveStone[i][j]->Draw();
		}
	}
	ResetMat();

	crypt->Draw();

	ResetMat();
	/*
	------------------------------------------------------------------------
	*/

	/*
	------------------------------------------------------------------------
	------------------------------------------------------------------------
				Set up 2D scene using orthographic mode
	------------------------------------------------------------------------
	------------------------------------------------------------------------
	*/

	//change the matrix mode to set up the HUD
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 800, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	healthBar->Draw();
	backGroundHealthBar->Draw();
	/*
	------------------------------------------------------------------------
	*/
	glFlush(); //flushes the scene drawn to the graphics card
	glutSwapBuffers();
}