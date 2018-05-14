#include "PWM.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
//PWM?????  
//arr:?????  
//psc:??????  
  
void TIM_PWM_Init(u16 arr,u16 psc)  
{    
    GPIO_InitTypeDef GPIO_InitStructure;  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);// ???????TIM2/TIM3/TIM4  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);  //??GPIOA/GPIOB??????  
                                                                              
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
      
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9; //TIM3?3?4??,TIM4?3?4??  
    GPIO_Init(GPIOB,&GPIO_InitStructure);       
  
      
    TIM_TimeBaseStructure.TIM_Period = arr; //???????????????????????????    50HZ  
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //??????TIMx???????????  ???  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //??????:TDTS = Tck_tim  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????  
      
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //??TIM_TimeBaseInitStruct?????????TIMx???????  
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //??TIM_TimeBaseInitStruct?????????TIMx???????  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //??TIM_TimeBaseInitStruct?????????TIMx???????  
  
   
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //???????:TIM????????1  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //??????  
    TIM_OCInitStructure.TIM_Pulse = 0; //????????????????  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //????:TIM???????  
  
  
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //??TIM_OCInitStruct???????????TIMx   
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH3?????     
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //??TIM_OCInitStruct???????????TIMx   
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH4?????  
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //??TIM_OCInitStruct???????????TIMx   
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH3?????     
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //??TIM_OCInitStruct???????????TIMx   
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH4?????     
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //??TIM_OCInitStruct???????????TIMx     
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH3?????     
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //??TIM_OCInitStruct???????????TIMx   
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH4?????  
      
      
    TIM_ARRPreloadConfig(TIM2, ENABLE); //??TIMx?ARR????????  
    TIM_CtrlPWMOutputs(TIM2,ENABLE);    //MOE ?????  
    TIM_Cmd(TIM2, ENABLE);  //??TIM2  
    TIM_ARRPreloadConfig(TIM3, ENABLE); //??TIMx?ARR????????  
    TIM_CtrlPWMOutputs(TIM3,ENABLE);    //MOE ?????  
    TIM_Cmd(TIM3, ENABLE);  //??TIM3  
    TIM_ARRPreloadConfig(TIM4, ENABLE); //??TIMx?ARR????????  
    TIM_CtrlPWMOutputs(TIM4,ENABLE);    //MOE ?????  
    TIM_Cmd(TIM4, ENABLE);  //??TIM4  
}  


void TIM_Configuration(void)  
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
    GPIO_InitTypeDef    GPIO_InitStructure;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 , ENABLE);  
      
      
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA,&GPIO_InitStructure);       
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 
    GPIO_Init(GPIOB,&GPIO_InitStructure);     
  
    TIM_TimeBaseStructure.TIM_Period =9999;           
    TIM_TimeBaseStructure.TIM_Prescaler =143;           
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;          
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;      
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);         
  
      
    TIM_OCStructInit(& TIM_OCInitStructure);      
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
    TIM_OCInitStructure.TIM_Pulse =0;                
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       
      
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);     
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);      
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
  
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);  
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);  
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);  
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);  
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  
    TIM_Cmd(TIM3, ENABLE);  
    TIM_CtrlPWMOutputs(TIM3, ENABLE);  
    TIM_Cmd(TIM4, ENABLE);  
    TIM_CtrlPWMOutputs(TIM4, ENABLE);           
}  
void SetJointAngle(u8 ID, float angle)  
{  
    switch(ID)  
    {  
        case 0:                                      //-90-->90   
            angle=angle+90.0;                        
            angle=(u16)(50.0*angle/9.0+249.0);       
            TIM_SetCompare1(TIM3,angle);          
            break;  
                                                 //0-->180
        case 1:  
            angle=(u16)(4.175*angle+409.25);  
            TIM_SetCompare2(TIM3,angle);            
            break;  
  
  
        case 2:                                    //-150-->0
            angle=-angle;  
            angle=(u16)(4.175*angle+480.0);  
            TIM_SetCompare1(TIM4,angle);  
            break;  
  
        case 3:  
            angle=-180-angle;  
            angle=-angle;  
            angle=(u16)(4.175*angle+315.0);  
          
  
            TIM_SetCompare2(TIM4,angle);  
            break;  
                                              //-90-->90
        case 4:  
            angle=90.0+angle;  
            angle=(u16)(249.0+50.0*angle/9.0);  
            TIM_SetCompare3(TIM4,angle);              
            break;   
  
  
        default: break;  
    }      
}  
