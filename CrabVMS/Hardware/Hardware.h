/******************** (C)Copyright wisearm.com *********************************
* File Name         : Hardware.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2016-02-18
* Last Update       : 2016-11-16
* Description       : Ӳ������������
********************************************************************************/
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f4xx.h"
#include "stm32ext.h"
#include "eeprom.h"
#include "spiflash.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_gap.h"
#include "nRF24L01.h"

#define SYS_LED       GPIO_PB2
#define SYS_ESC       GPIO_PC13
#define SYS_BEP       GPIO_PB6  
   
#define LED_1         GPIO_PA10
#define LED_2         GPIO_PB4
#define MOTO1_A       GPIO_PB6
#define MOTO1_B       GPIO_PB7
#define MOTO2_A       GPIO_PB6
#define MOTO2_B       GPIO_PB7   

#define KEY_1         GPIO_PB3
#define KEY_2         GPIO_PA15   
   
#define ADC_1      GPIO_PB0
#define ADC_2      GPIO_PB1
#define ADC_CH1    ADC_Channel_8
#define ADC_CH2    ADC_Channel_9

#define ADC_SimpleTime  ADC_SampleTime_56Cycles  

#define PRINTF_COM            USART1
#define USER_COM              USART1
#define PROTOCOL_COM          USART1
#define DEVICE_COM_BR         115200

extern __IO uint16_t         ADCValue[];

extern uint8_t nRF24_Channel;

void Hardware_Init(void);
void Device_Init(void);

#ifdef __cplusplus
}
#endif
#endif

