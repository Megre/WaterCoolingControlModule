
#include <reg51.h>

sbit IRIN = P3^2;         //���������������


void IRdelay(char x);  //x*0.14MS
void beep();

unsigned char  IRCOM[7];
extern unsigned char control_type;
extern void display(unsigned char Key_Val);
/*******************************************************************/
void IRInit()
{
    IE |= 0x81;                 //�������ж��ж�,ʹ�� INT0 �ⲿ�ж�
    TCON |= 0x01;               //������ʽΪ���帺���ش���
    
    IRIN=1;                    //I/O�ڳ�ʼ��
} 

/**********************************************************/
void IR_IN(void) interrupt 0 
{
    unsigned char j,k,N=0;
    EX0 = 0;  

    IRdelay(5);
    if (IRIN==1) 
    { 
        EX0 =1;
        return;
    } 
                           //ȷ��IR�źų���
    while (!IRIN)            //��IR��Ϊ�ߵ�ƽ������9ms��ǰ���͵�ƽ�źš�
    {IRdelay(1);}

    for (j=0;j<4;j++)         //�ռ���������
    { 
        for (k=0;k<8;k++)        //ÿ��������8λ
        {
            while (IRIN)            //�� IR ��Ϊ�͵�ƽ������4.5ms��ǰ���ߵ�ƽ�źš�
            {IRdelay(1);}
            while (!IRIN)          //�� IR ��Ϊ�ߵ�ƽ
            {IRdelay(1);}
            while (IRIN)           //����IR�ߵ�ƽʱ��
            {
                IRdelay(1);
                N++;           
                if (N>=30)
                { 
                    EX0=1;
                    return;
                }                  //0.14ms���������Զ��뿪��
            }                        //�ߵ�ƽ�������                
            IRCOM[j]=IRCOM[j] >> 1;                  //�������λ����0��
            if (N>=8) {IRCOM[j] = IRCOM[j] | 0x80;}  //�������λ����1��
            N=0;
            
            control_type = 'r';
        }//end for k
   	
    }//end for j
   
    if (IRCOM[2]!=~IRCOM[3])
    { 
        EX0=1;
        return; 
	}

    EX0 = 1; 
} 


/**********************************************************/
void IRdelay(unsigned char x)    //x*0.14MS
{
    unsigned char i;
    while(x--)
    {
    for (i = 0; i<13; i++) {}
    }
}



