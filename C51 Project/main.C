/********************************************************************************
*  描述:                                                                       *
*         数码管显示 遥控键值读取器                                            *
*         遥控器接p3.2                                                         *
*                                                                              *
*                                                                              *
*                                                                              *
*******************************************************************************/
#include <intrins.h>
#include <reg52.h>
#define  NOP() _nop_()  /* 定义空指令 */

unsigned char SenData,ReData,Flag;
unsigned char control_type = 'u'; // 'u': USB, 'r': 遥控
sbit PWR_LED = P2^0;

sbit ctrl0 = P1^0;
sbit ctrl1 = P1^1;
sbit ctrl2 = P1^2;

// 引用IR.C中的变量和函数
extern  unsigned char  IRCOM[7];
extern void IRInit(); 

void delay(unsigned int i);  
void shutdown(unsigned char key);
void initSerial();

main()
{ 
  IRInit();
  initSerial();

  ctrl0 = 0;
  ctrl1 = 0;
  ctrl2 = 0;
  PWR_LED = 0; // Power LED on
    while(1)
    { 
    // 接收红外并控制
    if(control_type == 'r') {
      shutdown(IRCOM[2]);       
    }
    
    // 串口控制
    else if (Flag==1)
    {
       EA=0; // 关总中断 
      
       if((ReData & 0x80) == 0x80) { // 最高位为1，控制开关
          ctrl0 = ((ReData & 1)==1?1:0);
          ctrl1 = ((ReData & 0x02)==0x02?1:0);
          ctrl2 = ((ReData & 0x04)==0x04?1:0);
       }

       SenData = (ReData & 0x80) | ctrl0 | (ctrl1*2) | (ctrl2*4);
       
       // 发送数据
       SBUF = SenData;  // SUBF接受/发送缓冲器
       while(TI==0);
       TI=0; // 发送中断标志
       Flag=0;
       EA=1; // 开总中断
    }
  } 
}


void shutdown(unsigned char key)
{ 
  if(key == 69)  { // 全开 
        if(ctrl0 != 1) ctrl0 = 1;
        if(ctrl1 != 1) ctrl1 = 1;
    if(ctrl2 != 1) ctrl2 = 1;
    }
    else if(key == 71) { // 全关
        if(ctrl0 != 0) ctrl0 = 0;
        if(ctrl1 != 0) ctrl1 = 0;
    if(ctrl2 != 0) ctrl2 = 0;
    }
    else if(key == 12){
        if(ctrl0 != 1) ctrl0 = 1;
    }
    else if(key == 24) {
    if(ctrl1 != 1) ctrl1 = 1;
    }
}

void delay(unsigned int i)
{
    char j;
    for(i; i > 0; i--)
        for(j = 200; j > 0; j--);
}

void initSerial() {
    SCON = 0x50;       // 串口方式1, 10位异步收发。REN=1允许串行接受状态
      TMOD|= 0x20;       // 定时器工作方式2，8位常数自动装入
    PCON|= 0x80;       // 波特率倍增
        //TH1 = 0xFD;     // baud*2  波特率19200、数据位8、停止位1。效验位无 (11.0592)
    //TL1 = 0xFD;
        //TH1 = 0xF3;                // baud*2  波特率4800、数据位8、停止位1。效验位无 (12M)
    //TL1 = 0xF3;
    TH1 = 0xF4;     // baud*2  波特率4800、数据位8、停止位1。效验位无 (11.0592)
    TL1 = 0xF4;
        TR1  = 1;        // TCON (D6)：定时器T1启动
        ES   = 1;        // 开串口中断
        EA   = 1;        // 开总中断
}
                                                    
/****************************************************
               串口中断程序
******************************************************/
void ser_int (void) interrupt 4 using 1
{
    if(RI == 1)        // 接收中断标志
    {
    control_type = 'u';
    
        RI = 0;         // 清除RI接受中断标志
        ReData = SBUF;  // SUBF接受/发送缓冲器
        // SenData = ReData;
        Flag=1; // 接收到数据
    }
}
