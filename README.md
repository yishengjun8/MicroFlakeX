# MicroFlakeX
* MicroFlakeX2是MicroFlakeX的升级版：[MicroFlakeX2](https://github.com/yishengjun8/MicroFlakeX2/)  
* `mfx`的目标是让Win桌面开发远离复杂的框架，`专注于开发和逻辑`，并且可以快速自定义背景、图片。  

## MicroFlakeX简介
* Mfx尽量的使用简单的逻辑和命令来降低难度。  
* 加载图片、文字简单，可以为控件设置自定义图片或者文字。  
* 支持控件叠放次序(每一个控件都有一个次序数字，数字越大越上层)和用户焦点。  

## MicroFlakeX适合哪些人  
* 1、GDI+、GDI、WinAPI的初学者  
* 2、设计模式初学者  
* 3、框架设计初学者  
 
## 未来的控件计划
  * MfxPage、MfxPageList、MfxForm、MfxMenu、MfxEdit、MfxRadioButton、MfxCheckButton  

## 注意事项
  * 当你注册消息或事件的时候，请注意添加`MfxRecvDefMessage`或者`DefWindowProc`来确保缺省的消息也正常响应。  
  * `MicroFlakeX1.0`是单线程的，内部的各种类都不是线程安全的，请不要多线程操作mfx内部成员。    

## 参考
  1、程序开始请使用`MfxApplication App;`来创建一个全局MfxApplication对象，这个MfxApplication对象代表了程序本身。  
  2、创建一个新的窗口请使用`MfxUI`这个类需要你提供一些必要的参数用以初始化窗口的风格和标题。  
  3、使用`MfxImage`来创建一张Mfx通用格式图片，注意，参数里面的`Gdiplus::Graphics* set`请填写你的`MfxUI::GetDefGraphics()`，当你创建了一张`MfxImage`，那么这张`MfxImage`只能使用在对应的`MfxUI`上。  
  4、`MfxButton`需要给定`MfxUI`，也就是创建在对应的`MfxUI`上面，然后你可以对`MfxButton`的背景等特效进行修改。  
  5、注册控件事件：RegControlEvent(&Button, MFXCONTROLEVENT_LBUTTONCLICK, (MFXUI_FUNC)&MyUI::Func);  
  6、更详细的参考请看参考示例的代码。  
