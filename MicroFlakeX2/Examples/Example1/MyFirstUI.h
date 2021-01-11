#pragma once

#include "MfxAppFramework.h"
#include "MfxButton.h" //引入MfxButton控件
#pragma comment(lib,"MfxAppFramework.lib") 
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
using namespace MicroFlakeX;


/*
* public继承MfxUI，然后就可以自定义UI了
*/
class MyFirstUI
	: public MfxUI
{
public:
	/*
	* MyFirstUI构造函数，和MfxUI保持一致
	*/
	MyFirstUI(GdipRect gdiRect, MfxStrW title);

protected:
	/*
	* 定义MfxButton控件
	* 定义三个标准的消息函数
	* 注意，如果要使得你的消息函数能被调用，请务必保持格式一致
	* 格式如下：
	* MfxReturn FuncName(WPARAM wParam, LPARAM lParam);
	*/
	int myMyTimer1_ID;
	MfxButton myButton1;
	MfxReturn OnMyTimer1(WPARAM wParam, LPARAM lParam);
	MfxReturn OnMyButton1Check1(WPARAM wParam, LPARAM lParam);
	MfxReturn OnMyButton1Check2(WPARAM wParam, LPARAM lParam);
};

