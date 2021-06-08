# MicroFlakeX  
* MFX的目标是让WinAPP开发完全可自定义，整个UI都是你的绘制区域！  
* MFX支持运行时‘动态调用’和运行时‘动态创建’，所以你完全可以将整个MFX当作只有一个MfxBase*基类来统一处理！  
___
# MicroFlakeX3简介  
MfxBase是一个支持反射的对象，所以它的子类在注册了MfxObject宏之后，也支持反射。  
MicroFlakeX3的一个思想就是：将一切对象都当作同一个MfxBase*来处理，但是他们有不同的行为，通过AutoFunc，就可以实现多态。MfxGlide和MfxSignal都是基于这个思想进行设计的。  
当你真正明白MFX3的设计思路之后，你会发现，MicroFlakeX3虽然是C++语言，但是他竟然拥有堪比解释语言的动态能力！  

## MicroFlakeX3包含以下对象  
> MfxBase：MFX基类。支持继承的反射、工厂  
> MfxParam：MFX参数包，支持任意临时变量的异步传参  
> MfxSignal：MFX信号槽，可以添加任意对象的任意方法为接收者(运行时根据字符串动态绑定接收函数)，支持异步消息和同步消息  
> MfxMemberLock：MFX成员锁，可以对任意成员变量上锁  
> MfxType：MFX基本类型  
> MfxGlide：MFX变换。根据字符串动态绑定对象属性进行更改(缓动动画基于此实现)  
> MfxGraph：MFX基本绘制，基于D2D1(包含MfxCanvas-MfxImage-MfxWorlds)  
> MfxAppFrame：MFX程序框架 ，包含MfxUI、MfxFlake  

## 编译准备
1、请检查项目属性是否包含了其所需要的链接  
>> 配置属性-调试-环境 = PATH=..\..\lib_Debug  
>> C/C++-常规-附加包含目录 = ..\..\MicroFlakeX\include
>> 连接器-常规-附加库目录 = ...\..\lib_Debug  
2、请检查您的项目是否为“Debug - x86”编译模式  























