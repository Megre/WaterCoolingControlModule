# WaterCoolingControlModule
<img src="https://raw.githubusercontent.com/Megre/Media/main/PCB.jpg" alt="PCB" style="zoom:50%;" />

笔记本水冷控制模块，使用蓝牙串口（SPP）或USB串口控制风扇、水泵的通断。

使用DC12V6A接口供电。

工程主要包括：

- PCB设计

- 3D外壳模型

- C51串口控制源码



## 典型的外置水冷模块

<img src="https://raw.githubusercontent.com/Megre/Media/main/202472013169.jpg" alt="202472013169" style="zoom: 25%;" />



外置水冷通常用于笔记本。

典型的外置水冷由散热片（风扇）、水泵（图示为外置水泵）、水槽、导管、CPU端导热铜片等组成。



## 界面程序

使用USB串口控制开关通断，使用一个字节进行数据通信。

串口界面程序：[SwitchOnOff](https://github.com/Megre/SwitchOnOff)

![image-20231121145755749](https://renhao-picgo.oss-cn-beijing.aliyuncs.com/img/image-20231121145755749.png)



## DIY Tips

DC12V6A电源输入应该注意插头规格，插接松动容易引起发热。

工作原理是单片机IO控制MOS开关通断（蓝牙透传）。

