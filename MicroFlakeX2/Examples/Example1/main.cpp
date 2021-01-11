/*
* Example1 将向你展示如何导入Mfx并且创建一个自定义窗口
* x64
*/

#include "MyFirstUI.h"

MfxApplication myApp;
int main()
{
	MyFirstUI myUI(GdipRect(400, 200, 600, 300), L"Hello, MicroFlakeX!");

	return myApp.Run();
}