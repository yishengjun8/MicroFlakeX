#include "MyFirstUI.h"


/*
* 在MyFirstUI构造函数中，显示的调用MfxUI的构造函数，否则将无法成功创建窗口
*/
MyFirstUI::MyFirstUI(GdipRect gdiRect, MfxStrW title)
	: MfxUI(gdiRect, title)
{
	/*
	* 使用myMyTimer1_ID = 1，来构造一个每5000毫秒循环一次的Timer
	* 
	* 也就说，MyFirstUI::OnMyTimer1这个函数，将会每5000毫秒执行一次
	* 
	* 可以使用使用RemoveTimer(id)来移除不需要的Timer
	*/
	myMyTimer1_ID = 1;
	UI_ADD_TIMER(myMyTimer1_ID, 5000, MyFirstUI::OnMyTimer1);


	/*
	* 为UI添加控件，如果不使用AddControl，将无法使用myButton1
	* 使用myButton1之前必须将其绑定到一个UI上
	* 
	* UI_ADD_CONMSG为UI绑定一个控件事件，如果控件发生了对应的事件
	* 将会自动调用对应的方法进行处理
	*/
	AddControl(&myButton1);
	UI_ADD_CONMSG(&myButton1, MfxControl_Message_LButtonClick, MyFirstUI::OnMyButton1Check2);
	UI_ADD_CONMSG(&myButton1, MfxControl_Message_RButtonClick, MyFirstUI::OnMyButton1Check1);
	myButton1.SetRect(GdipRect(20, 20, 400, 200));
	myButton1.SetTitle(L"<右键单击开启‘左键按下移动按钮’功能>\n\n<每隔5秒会关闭一次本功能>\n\n<MfxUI默认开启自动调整控件大小，左键单击本按钮关闭>");


	/*
	* t_Image内部分重要方法支持反射调用
	* 
	* t_Image.AutoFunc(L"SetSize", GdipSize(200, 200));
	* 等价于
	* t_Image.SetSize(GdipSize(200, 200));
	*/
	MfxImage t_Image;
	t_Image.AutoFunc(L"SetSize", GdipSize(200, 200));
	//t_Image.SetSize(GdipSize(200, 200));
	t_Image.FromColor(GdipColor::DarkBlue);

	SetBigIcon(&t_Image);
}

MfxReturn MyFirstUI::OnMyTimer1(WPARAM wParam, LPARAM lParam)
{
	/*
	* wParam = 多少秒执行一次
	* lParam = 距离上一次执行，过去了多少秒
	*/
	myButton1.CloseLButtonMove();
	return MfxFine;
}

MfxReturn MyFirstUI::OnMyButton1Check1(WPARAM wParam, LPARAM lParam)
{
	/*
	* 开启控件左键按下移动
	*/
	myButton1.OpenLButtonMove();
	return MfxFine;
}

MfxReturn MyFirstUI::OnMyButton1Check2(WPARAM wParam, LPARAM lParam)
{
	/*
	* 关闭百分比位置
	* 
	* 如果想开启百分比位置请使用ResetPercentRect();
	* 
	* 百分比位置：控件会根据窗口大小，自动缩放。
	*/
	ClosePercentRect();
	return MfxFine;
}
