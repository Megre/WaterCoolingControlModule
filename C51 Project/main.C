/********************************************************************************
*  ����:                                                                       *
*         �������ʾ ң�ؼ�ֵ��ȡ��                                            *
*         ң������p3.2                                                         *
*                                                                              *
*                                                                              *
*                                                                              *
*******************************************************************************/
#include <intrins.h>
#include <reg52.h>
#define  NOP() _nop_()  /* �����ָ�� */

unsigned char SenData,ReData,Flag;
unsigned char control_type = 'u'; // 'u': USB, 'r': ң��
sbit PWR_LED = P2^0;

sbit ctrl0 = P1^0;
sbit ctrl1 = P1^1;
sbit ctrl2 = P1^2;

// ����IR.C�еı����ͺ���
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
    // ���պ��Ⲣ����
    if(control_type == 'r') {
      shutdown(IRCOM[2]);       
    }
    
    // ���ڿ���
    else if (Flag==1)
    {
       EA=0; // �����ж� 
      
       if((ReData & 0x80) == 0x80) { // ���λΪ1�����ƿ���
          ctrl0 = ((ReData & 1)==1?1:0);
          ctrl1 = ((ReData & 0x02)==0x02?1:0);
          ctrl2 = ((ReData & 0x04)==0x04?1:0);
       }

       SenData = (ReData & 0x80) | ctrl0 | (ctrl1*2) | (ctrl2*4);
       
       // ��������
       SBUF = SenData;  // SUBF����/���ͻ�����
       while(TI==0);
       TI=0; // �����жϱ�־
       Flag=0;
       EA=1; // �����ж�
    }
  } 
}


void shutdown(unsigned char key)
{ 
  if(key == 69)  { // ȫ�� 
        if(ctrl0 != 1) ctrl0 = 1;
        if(ctrl1 != 1) ctrl1 = 1;
    if(ctrl2 != 1) ctrl2 = 1;
    }
    else if(key == 71) { // ȫ��
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
    SCON = 0x50;       // ���ڷ�ʽ1, 10λ�첽�շ���REN=1�������н���״̬
      TMOD|= 0x20;       // ��ʱ��������ʽ2��8λ�����Զ�װ��
    PCON|= 0x80;       // �����ʱ���
        //TH1 = 0xFD;     // baud*2  ������19200������λ8��ֹͣλ1��Ч��λ�� (11.0592)
    //TL1 = 0xFD;
        //TH1 = 0xF3;                // baud*2  ������4800������λ8��ֹͣλ1��Ч��λ�� (12M)
    //TL1 = 0xF3;
    TH1 = 0xF4;     // baud*2  ������4800������λ8��ֹͣλ1��Ч��λ�� (11.0592)
    TL1 = 0xF4;
        TR1  = 1;        // TCON (D6)����ʱ��T1����
        ES   = 1;        // �������ж�
        EA   = 1;        // �����ж�
}
                                                    
/****************************************************
               �����жϳ���
******************************************************/
void ser_int (void) interrupt 4 using 1
{
    if(RI == 1)        // �����жϱ�־
    {
    control_type = 'u';
    
        RI = 0;         // ���RI�����жϱ�־
        ReData = SBUF;  // SUBF����/���ͻ�����
        // SenData = ReData;
        Flag=1; // ���յ�����
    }
}