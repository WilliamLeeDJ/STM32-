#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_spi_nrf.h"
#include "delay.h"
#include "bsp_adc.h"
#include "bsp_led.h"

#define uint unsigned int

u8 status;	
u8 txbuf[16]={0,1,2,3,1,1,1,1,1,1,1,1,1,1,1,1};	 
u8 rxbuf[16];			 
u8 port[4];
uint16_t time;
int i=0;

extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

uint ADC_ConvertedValueLocal[NOFCHANEL];        


void ALL_config()
{
	SPI_NRF_Init();
  USART_Config();
  ADCx_Init();
	LED_GPIO_Config();	 
}

void Test_connection()
{

  status = NRF_Check();   		
  if(status == SUCCESS)	   
    printf("\r\nNRF与主板连接成功\r\n");  
  else	  
    printf("\r\n请检查接线\r\n");

}


void transfer_dataPACK()
{
    NRF_TX_Mode();
   status = NRF_Tx_Dat(txbuf);	
//    if(status == TX_DS)

}



int main(void)                  
{ 
	ALL_config();
	  Test_connection();

  while(1)
  {
		ADC_ConvertedValueLocal[0] =(uint) ADC_ConvertedValue[0];
		ADC_ConvertedValueLocal[1] =(uint) ADC_ConvertedValue[1];
		ADC_ConvertedValueLocal[2] =(uint) ADC_ConvertedValue[2];
		ADC_ConvertedValueLocal[3] =(uint) ADC_ConvertedValue[3];
		
		if(ADC_ConvertedValueLocal[0]>4500)
			ADC_ConvertedValueLocal[0]=3000;
		if(ADC_ConvertedValueLocal[1]>4500)
			ADC_ConvertedValueLocal[1]=3000;
		if(ADC_ConvertedValueLocal[2]>4500)
			ADC_ConvertedValueLocal[2]=3000;
		if(ADC_ConvertedValueLocal[3]>4500)
			ADC_ConvertedValueLocal[3]=3000;
		
      printf("ADC1=%d\n",ADC_ConvertedValue[0]);
		  printf("ADC2=%d\n",ADC_ConvertedValue[1]);
      printf("ADC3=%d\n",ADC_ConvertedValue[2]);
      printf("ADC4=%d\n",ADC_ConvertedValue[3]);

			txbuf[0]=ADC_ConvertedValueLocal[0]/1000%10;
			txbuf[1]=ADC_ConvertedValueLocal[0]/100%10;
			txbuf[2]=ADC_ConvertedValueLocal[0]/10%10;
			txbuf[3]=ADC_ConvertedValueLocal[0]/1%10;
		
			txbuf[4]=ADC_ConvertedValueLocal[1]/1000%10;
			txbuf[5]=ADC_ConvertedValueLocal[1]/100%10;
			txbuf[6]=ADC_ConvertedValueLocal[1]/10%10;
			txbuf[7]=ADC_ConvertedValueLocal[1]/1%10;
		
			txbuf[8]=ADC_ConvertedValueLocal[2]/1000%10;
			txbuf[9]=ADC_ConvertedValueLocal[2]/100%10;
			txbuf[10]=ADC_ConvertedValueLocal[2]/10%10;
			txbuf[11]=ADC_ConvertedValueLocal[2]/1%10;
		
		  txbuf[12]=ADC_ConvertedValueLocal[3]/1000%10;
			txbuf[13]=ADC_ConvertedValueLocal[3]/100%10;
			txbuf[14]=ADC_ConvertedValueLocal[3]/10%10;
			txbuf[15]=ADC_ConvertedValueLocal[3]/1%10;
				
		  transfer_dataPACK();
			if(status == RX_DR)
				LED2(1);
			else
				LED2(0);
  }
}
