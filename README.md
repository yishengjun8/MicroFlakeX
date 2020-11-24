# MicroFlakeX

* mfx是一个运行在`Windows`上的精巧的`DirectUI`框架库。  
* `mfx`的目标是让Win桌面开发远离复杂的框架，`专注于开发和逻辑`，并且可以快速自定义背景、图片和蒙版，让你的程序充满自己的美术风格。  
* 当你需要快速开发一款软件，而不想使用`复杂的框架`和学习`复杂的控件调用方法`，mfx就是你最好的选择。  

## MFX有哪些优点
* 上手极其简单，关键代码就那么几行，mfx尽量的使用简单的逻辑和命令来降低学习难度。
* 加载图片、文字非常简单，可以快速为控件设置自定义图片或者文字。
* 非常容易注册新的事件，仅仅需要一行代码就可以注册成功！
* 非常便捷的使用定时器！定时器会定时发送你的自定义消息！你可以为你的自定义消息添加自定义事件。
* 支持控件叠放次序(每一个控件都有一个次序数字，数字越大越上层)和用户焦点指示。

## 未来的控件计划：
  MfxButton、MfxPage、MfxPageList、MfxForm、MfxMenu、MfxEdit、MfxRadioButton、MfxCheckButton
  说实话，我想专注于开发框架，虽然控件也是框架的一部分吧。希望各位能加入控件开发，为mfx提交贡献！

## 注意事项：
  当你注册消息或事件的时候，请注意添加`MfxRecvDefMessage`或者`DefWindowProc`来确保缺省的消息也正常响应！  
  `MicroFlakeX1.0`是单线程的，内部的各种类都不是线程安全的，请不要多线程操作mfx内部成员；  
  `MicroFlakeX2.0`预计会支持多线程，同时重构部分逻辑。

## 参考文档:
1、程序开始请使用`MfxApplication App;`来创建一个全局MfxApplication对象，这个MfxApplication对象代表了程序本身。  
2、创建一个新的窗口请使用`MfxUI`这个类需要你提供一些必要的参数用以初始化窗口的风格和标题！  
3、使用`MfxImage`来创建一张Mfx通用格式图片，注意，参数里面的`Gdiplus::Graphics* set`请填写你的`MfxUI::GetDefGraphics()`，当你创建了一张`MfxImage`，那么这张`MfxImage`只能使用在对应的`MfxUI`上！  
4、`MfxButton`需要给定`MfxUI`，也就是创建在对应的`MfxUI`上面，然后你可以对`MfxButton`的背景等特效进行修改。  
5、注册控件事件：RegControlEvent(&Button, MFXCONTROLEVENT_LBUTTONCLICK, (MFXUI_FUNC)&MyUI::Func);  
6、更详细的参考请看参考示例的代码！  
