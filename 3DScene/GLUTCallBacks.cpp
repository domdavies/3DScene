#include "3DScene.h"
#include "GlutCallBacks.h"


namespace GLUTCallBacks
{
	namespace
	{
		HelloGL* helloGL = nullptr;
	}
	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}

	void Display()
	{
		//if the game (helloGL) is not a nullptr, then run the display function
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}

	void Timer(int preferedRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		helloGL->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferedRefresh - updateTime, GLUTCallBacks::Timer, preferedRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key, x, y);
	}

	void MouseButton(int button, int state, int x, int y)
	{
		helloGL->MouseButton(button, state, x, y);
	}

	void MouseMove(int x, int y) {
		helloGL->MouseMove(x, y);
	}

	void SpecialKeys(int key, int x, int y) {
		helloGL->SpecialKeys(key, x, y);
	}
}