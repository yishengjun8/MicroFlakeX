## MicroFlakeX3简介   
* MfxControl支持线性插值动画，支持：变速滑动、曲线移动等。
* MfxBase反射框架，新增：全能工厂、反射继承、优先初始化。 
# MicroFlakeX3  
* MicroFlakeX3包含:  
> MfxBase：MFX基类。支持反射、工厂模式、线程安全  
> MfxType：MFX基本类型(包含了Rect、Size、Point、Color等基本类型)  
> MfxGraph：MFX基本绘制，基于D2D1(包含MfxCanvas-MfxImage-MfxWorlds-MfxShape-MfxEffect)  
> MfxAppFrame：MFX程序框架 ，包含MfxApp、MfxFlake  

## MicroFlakeX3参考  
请下载并阅读Examples内的示例代码，里面详尽的展示了MicroFlakeX3的全部功能示范。

## 编译准备
1、请检查项目属性是否包含了其所需要的链接。  
>> C/C++-常规-附加包含目录 = ..\..\MfxBase\MfxBase;..\..\Mfx  
>> 连接器-常规-附加库目录 = ..\..\MfxBase\MfxBase\Debug;..\..\Mfx  

2、请检查是否将编译生成的.dll文件放置在您的工程目录下  
3、请检查您的项目是否为x86编译模式  

