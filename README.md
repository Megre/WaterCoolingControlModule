# WaterCoolingControlModule
<img src="https://renhao-picgo.oss-cn-beijing.aliyuncs.com/img/image-20231108162739160.png" alt="image-20231108162739160" style="zoom:67%;" />

笔记本水冷控制模块，使用遥控和USB串口控制风扇、水泵、半导体制冷片的通断。实质是5路的遥控+USB串口双控通断开关，可用于类似应用。

应用场景：

- 遥控控制，方便控制模块的布线，简化办公桌面布局
- 远程控制电脑时，通过[USB串口控制水冷](https://github.com/Megre/SwitchOnOff)（例如用向日葵远程登录带水冷模块的笔记本）

模块用手头的51单片机及外围电路搭建。通断线路共5路，包括3路DC（5.5*2.1）和2路Type-C。使用Type-C接口供电或接PC端。

测试稳定功率12V/5A。



## 典型的外置水冷模块

<img src="https://renhao-picgo.oss-cn-beijing.aliyuncs.com/img/image-20231108163113782.png" alt="image-20231108163113782" style="zoom: 33%;" />

外置水冷通常用于笔记本。

典型的外置水冷由散热片（风扇）、水泵、半导体制冷片、水槽、导管等组成。



## DIY Tips

工作原理是单片机IO控制MOS开关通断。

红外遥控通过PWM控制。

串口使用一个字节进行数据通信。串口界面程序：[SwitchOnOff](https://github.com/Megre/SwitchOnOff)
