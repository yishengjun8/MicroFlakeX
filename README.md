# MicroFlakeX  
* MFX的目标是让WinAPP开发完全可自定义，整个UI都是你的绘制区域！  
* MFX支持运行时‘动态调用’和运行时‘动态创建’，所以你完全可以将整个MFX当作只有一个MfxBase*基类来统一处理！  
[MicroFlakeX1](README.md#MicroFlakeX1简介)  
[MicroFlakeX2](README.md#MicroFlakeX2简介)  
[MicroFlakeX3](README.md#MicroFlakeX3简介)  
___
# MicroFlakeX3简介  
`MicroFlakeX3`在MFX2的基础上，重写了MfxGraph，重构了MfxBase基类。使其拥有更好的扩展性和阅读性。  
由于MfxBase是一个支持反射的对象，所以它的子类在注册了MfxObject宏之后，也支持反射。  
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
>> C/C++-常规-附加包含目录 = ..\..\MfxBase\MfxBase  
>> 连接器-常规-附加库目录 = ...\..\lib_Debug  
2、请检查您的项目是否为“Debug - x86”编译模式  

___
#### MicroFlakeX2简介  
`MicroFlakeX2`在MFX1的基础上，进一步分离和模块化。它实现了一个稍微复杂的多层消息队列转发和UI创建。多层消息队列转发是不常见的转发机制，例如在MFC中，消息一般只会传递映射一次。同时MFX2还提供了反射框架。虽然并不完美，但是总归体现了设计思路。同时MFX2提供了线程安全保护。这同样值得学习  

###### MicroFlakeX2介绍  
* MfxBasicModules负责提供WinApp基础，例如绘制图像等  
* MfxAppFramework负责构造WinApp框架，例如发送消息，响应事件
* MFX2提供了支持线程安全的基类  
* MFX2采用`事件-方法队列`的模式处理消息，也就是说你可以自定义你的消息处于响应队列的前或后。同一个消息可以被多次顺序响应。最终的返回值取决于最后一个响应的消息如何返回  

#### 注意！！MicroFlakeX2已经放弃维护，也就是说MFX2不再更新和提供帮助支持，仅供学习参考  


____
#### MicroFlakeX1简介
`MicroFlakeX1`是一个简陋而空旷的框架。它仅仅实现了一个最简单的二层消息映射转发和UI创建但这并不表明MFX1是无用的，MFX1虽然简单，但他体现了如何构造UI框架的思路和设计模式，非常适合初学者参考和学习。

###### MicroFlakeX1适合哪些人  
* 1、GDI+、GDI、WinMain、WinAPI的初学者  
* 2、设计模式初学者  
* 3、框架设计初学者  

#### 注意！！MicroFlakeX1已经放弃维护，也就是说MFX1不再更新和提供帮助支持，仅供学习参考  























