#pragma once

class HelloGL;

namespace GLUTCallBacks
{
	void Init(HelloGL* gl);
	void Display();
	void Timer(int preferedRefresh);
	void Keyboard(unsigned char key, int x, int y);
	void MouseButton(int button, int state, int x, int y);
	void MouseMove(int x, int y);
	void SpecialKeys(int key, int x, int y);
}