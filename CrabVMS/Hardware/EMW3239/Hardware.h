/******************** (C)Copyright wisearm.com *********************************
* File Name         : Hardware.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2016-02-18
* Last Update       : 2016-11-16
* Description       : 硬件配置与设置
********************************************************************************/
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f4xx.h"
#include "stm32ext.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_gap.h"

#define SYS_LED       GPIO_PA10
#define SYS_ESC       GPIO_PA15
#define SYS_BEP       0
#define BEP_TIM       0
#define BEP_CHANNEL   0
   
#define LED_1         GPIO_PC0
#define LED_2         GPIO_PB4
   
#define KEY_1         GPIO_PB10
#define KEY_2         GPIO_PC13
//#define KEY_SCAN      1
   
#define ADC_1         GPIO_PA4
#define ADC_2         GPIO_PA5
#define ADC_CH1       ADC_Channel_4
#define ADC_CH2       ADC_Channel_5

#define ADC_SimpleTime  ADC_SampleTime_56Cycles  
   
#define MOTO1_TIM     2
#define MOTO1_A_IO    GPIO_PB3
#define MOTO1_A_CH    2
#define MOTO1_B_IO    0
#define MOTO1_B_CH    0
   
#define MOTO2_TIM     0
#define MOTO2_A_IO    0
#define MOTO2_A_CH    0
#define MOTO2_B_IO    0
#define MOTO2_B_CH    0

#define PRINTF_COM            USART1
#define USER_COM              USART1
#define PROTOCOL_COM          USART1
#define DEVICE_COM_BR         115200

extern __IO uint16_t         ADCValue[];

extern uint8_t nRF24_Channel;

#define GPIO_ADDR_MAX 16
extern const uint32_t GPIO_ADDR[];

void Hardware_Init(void);
void Device_Init(void);

#ifdef __cplusplus
}
#endif
#endif

