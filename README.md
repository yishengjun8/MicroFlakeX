# MicroFlakeX

* 一个运行在`Windows`上的简单`DirectUI`库。
* `MFX`的目标是让桌面开发远离复杂的框架，专注于开发和逻辑本身

## 未来的控件计划：
  MfxButton.h、MfxMenu.h、MfxForm、MfxEdit.h、MfxRadioButton、MfxCheckButton.h

## 注意事项：
  当你注册消息或事件的时候，请注意添加`MfxRecDefMessage`或者`DefWindowProc`来确保缺省的消息也正常响应！  
  目前的`MicroFlakeX不是多线程`，也就是说可能会存在界面卡死的问题！请注意！

## 参考文档:

1、程序开始请使用`MfxApplication App;`来创建一个全局MfxApplication对象，这个MfxApplication对象代表了程序本身。

2、创建一个新的窗口请使用`MfxUI`这个类需要你提供一些必要的参数用以初始化窗口的风格和标题！

3、使用`MfxImage`来创建一张Mfx通用格式图片，注意，参数里面的`Gdiplus::Graphics* set`请填写你的`MfxUI::GetBuffGraphics()`，当你创建了一张`MfxImage`，那么这张`MfxImage`只能使用在对应的`MfxUI`上！

4、`MfxButton`需要给定`MfxUI`，也就是创建在对应的`MfxUI`上面，然后你可以对`MfxButton`的背景等特效进行修改。

5、注册控件事件：RegControlEvent(&Button, MFXCONTROLEVENT_LBUTTONCLICK, (MFXUI_FUNC)&MyUI::???);

6、更详细的参考请看参考示例的代码！
