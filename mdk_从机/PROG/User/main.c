#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_spi_nrf.h"
#include "pwm.h"
//#include "bsp_led.h"

u8 status;		 
u8 txbuf[16];	 
u8 rxbuf[16];	 
u8 i; 
uint16_t ch1;
uint16_t ch2;
uint16_t ch3;
uint16_t ch4;


void Config_ALL()
{
  USART_Config(); 
  SPI_NRF_Init(); 

}


void Test_connection()
{

  status = NRF_Check();   		
  if(status == SUCCESS)	   
    printf("\r\nNRF与主板连接成功\r\n");  
  else	  
    printf("\r\n请检查接线\r\n");

}


void Transfer_Datapack()
{
    NRF_RX_Mode();
    status = NRF_Rx_Dat(rxbuf);
    /*判断接收状态*/
    if(status == RX_DR)
    {
     ch1=rxbuf[0]*1000+rxbuf[1]*100+rxbuf[2]*10+rxbuf[3];
		 ch2=rxbuf[4]*1000+rxbuf[5]*100+rxbuf[6]*10+rxbuf[7];
     ch3=rxbuf[8]*1000+rxbuf[9]*100+rxbuf[10]*10+rxbuf[11];
     ch4=rxbuf[12]*1000+rxbuf[13]*100+rxbuf[14]*10+rxbuf[15];
			
			printf("ch1=%d\n",ch1);
//			printf("ch2=%d\n\n\n",ch2);
//			printf("ch3=%d\n",ch3);
//			printf("ch4=%d\n",ch4);
    }     

}


int main(void)
{ 
	u16 pwmval1=750;//50->0.1ms
	u16 pwmval2=750;//舵机遵循1ms45度，1.5ms中立，2ms135度
	u16 pwmval3=750;
	u16 pwmval4=750;

	Config_ALL();
  Test_connection();
	TIM_PWM_Init(9999,143);
	printf("\r\nNRF与主板连接成功\r\n"); 
  while(1)
  {  		 	
    Transfer_Datapack();
		
	/*	if(ch1<=3000) pwmval1=ch1/12+500;
		if(ch1>3000) pwmval1=ch1/4;
		if(ch2<=2200) pwmval2=ch2*0.16+300-20;
		if(ch2>2200) pwmval2=ch2*0.17+443.85;
		*/
//		
//				
		if(ch1<=3200) pwmval1=ch1*0.08+492.77;
		if(ch1>3200) pwmval1=ch1*0.391-501.39;
		
		
		if(ch2<=3000) pwmval2=ch2*0.1504+298.79;
		if(ch2>3000) pwmval2=ch2*0.3196-208.904;
		
//		
//		if(ch4<=3000) pwmval4=ch4/12+500;
//		if(ch4>3000) pwmval4=ch4/4;
//		if(ch3<=3000) pwmval3=(ch3+4500)/10;  
//		if(ch3>3000) pwmval3=ch3/4;
//		

		printf("pwmval1=%d\n",pwmval1);
		printf("pwmval2=%d\n",pwmval2);
	//	printf("pwmval2=%d\n",pwmval2);
//		printf("pwmval4=%d\n",pwmval4);

		TIM_SetCompare3(TIM3,pwmval1);//PB0
		TIM_SetCompare3(TIM4,pwmval2);//PB8
	


		TIM_SetCompare4(TIM2,pwmval3);//PA3
		TIM_SetCompare4(TIM4,pwmval4);//PB9
	
		
  } 
}
