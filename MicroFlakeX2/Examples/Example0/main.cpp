/*
* Example0将向你展示如何导入Mfx并且创建一个最简单的窗口
*/


/*
* 使用MicroFlakeX需要引入MicroFlakeX库
* 并且调用MicroFlakeX的lib链接库
*/
#include "MfxAppFramework.h"
#pragma comment(lib,"MfxAppFramework.lib") 

/*
* 告诉编译器不要弹出黑色窗口
*/
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

/*
* 引入MicroFlakeX命名空间，Mfx都在MicroFlakeX这个命名空间内
* 
* 为了防止冲突，也可以使用作用于标识符引用
*/
using namespace MicroFlakeX;

/*
* 必须在程序运行的最开始，定义一个MfxApplication
* 
* MfxApplication代表Mfx本身，必须且仅能创建一个
* 
* 单例模式
*/
MfxApplication myApp; 

int main()
{
	/*
	* 创建一个MfxUI
	* 
	* 第一个参数是窗口位置GdipRect(X,Y,Wi,Hi)
	* 第二个参数是窗口名字
	*/
	MfxUI myUI(GdipRect(400,200,600,300), L"Hello, MicroFlakeX!");

	/*
	* 创建一张图片
	* 
	* 设置图片大小，因为图片初始大小为1，1，太小了。
	* 为图片加载颜色
	*/
	MfxImage myImage;
	myImage.SetSize(GdipSize(200, 200));
	myImage.FromColor(GdipColor::Red);

	/*
	* 利用刚刚的MfxImage设置myUI的图标
	* 
	* 同时为myUI设置背景颜色
	*/
	myUI.SetBigIcon(&myImage);
	myUI.SetBackColor(GdipColor::Blue);

	/*
	* 开始消息循环
	*/
	return myApp.Run();
}