## MicroFlakeX3简介  
* MfxUI是多线程的，界面更新与业务代码分离，相互之间不会影响卡死。  
* MfxControl支持线性插值动画，支持：变速滑动、曲线移动等。不支持旋转。
* MfxBase反射框架，新增：全能工厂、反射继承、优先初始化。 
# MicroFlakeX3  
* MicroFlakeX3包含:  
> MfxBase：MFX基类。支持反射、工厂模式、线程安全  
> MfxType：MFX基本类型(包含了Rect、Size、Point、Color等基本类型)  
> MfxGraph：MFX基本绘制，基于D2D1(包含MfxCanvas-MfxImage-MfxWorlds-MfxShape-MfxEffect)  
> MfxAppFrame：MFX程序框架  
## MicroFlakeX3参考  
请下载并阅读Examples内的示例代码，里面详尽的展示了MicroFlakeX3的全部功能示范。