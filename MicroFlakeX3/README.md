# MicroFlakeX3包含以下对象  
> MfxBase：MFX基类。支持继承的反射、工厂  
> MfxParam：MFX参数包，支持任意临时变量的异步传参  
> MfxSignal：MFX信号槽，可以添加任意对象的任意方法为接收者，支持异步消息和同步消息  
> MfxMemberLock：MFX成员锁，可以对任意成员变量上锁  
> MfxType：MFX基本类型  
> MfxGlide：MFX变换。根据字符串动态绑定对象属性进行更改(缓动动画基于此实现)  
> MfxGraph：MFX基本绘制，基于D2D1(包含MfxCanvas-MfxImage-MfxWorlds)  
> MfxAppFrame：MFX程序框架 ，包含MfxUI、MfxFlake  

## 编译准备
1、请检查项目属性是否包含了其所需要的链接  
>> 配置属性-调试-环境 = PATH=..\..\lib_Debug  
>> C/C++-常规-附加包含目录 = ..\..\MfxBase\MfxBase  
>> 连接器-常规-附加库目录 = ...\..\lib_Debug  
2、请检查您的项目是否为“Debug - x86”编译模式  

