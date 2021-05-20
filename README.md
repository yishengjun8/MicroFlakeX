# MicroFlakeX  
* MFX的目标是让WinAPP开发远离复杂的框架，专注于开发本身  
* MFX可以自定义控件、窗口的背景图片、蒙版，让你的程序变得更加好看  
* MFX支持运行时动态调用和运行时动态创建  
* MFX支持GPU渲染  

[MicroFlakeX1](README.md#MicroFlakeX1简介)  
[MicroFlakeX2](README.md#MicroFlakeX2简介)  
[MicroFlakeX3](README.md#MicroFlakeX3简介)  
___
# MicroFlakeX3简介  
`MicroFlakeX3`在MFX2的基础上，重写了MfxGraph，重构了MfxBase基类。拥有更好的扩展性和阅读性。同时顶层App框架支持更多的特性，其操作也进一步通过宏简化  

* MfxBase基类支持：工厂、反射、信号槽、线程池、改动标志   
* MfxGraph为Direct2D绘制，更快的刷新和图片支持(60帧很轻松)  
* MfxFlake(原MfxControl)支持线性动画。暂不支持旋转  


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























