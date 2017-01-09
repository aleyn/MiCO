/******************** Copyright wisearm.com *********************************
* File Name         : CrabVMS.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �����ļ�
********************************************************************************/

#ifndef __CRAB_VMS_MANAGE__
#define __CRAB_VMS_MANAGE__

#include "CrabHardware.h"
#include "CrabConfig.h"
#include "CrabBaseType.h"
#include "CrabErrorMsg.h"
#include "CrabString.h"
#include "CrabStream.h"
#include "CrabStoreStream.h"
#include "CrabStorage.h"
#include "CrabExecute.h"
#include "CrabExtern.h"
#include "CrabDefaultApi.h"
#include "CrabDatetime.h"
#include "CrabFifo.h"
#include "CrabPlatform.h"
#include "CrabNet.h"

#ifdef  __cplusplus
extern "C" {
#endif
  
//�汾��Ϣ
#define CRAB_DEVICE_ID            101
#define CRAB_VENDER_ID            2282902
#define CRAB_HW_VER               0x0101
    
#define CRAB_LED_OFF              0x00
#define CRAB_LED_GREEN_ON         0x01
#define CRAB_LED_RED_ON           0x02
#define CRAB_LED_GREEN_FLASH      0x11
#define CRAB_LED_RED_FLASH        0x12
#define CRAB_LED_GREEN_ERROR      0x21
#define CRAB_LED_RED_ERROR        0x22
  
#define CRAB_BEEP_STOP            0x00
#define CRAB_BEEP_START           0x01
  
#define CRAB_TASK_SYSTEM          0x01
#define CRAB_TASK_COMMAND         0x02
#define CRAB_TASK_APPLICATION     0x03
#define CRAB_TASK_EVENT           0x04

//���������
void CrabSystem_Running();

//��������
void CrabCreateTask(CrabByte TaskID);

//��������
void CrabTaskSuspend(CrabByte TaskID);
void CrabTaskSuspendFromISR(CrabByte TaskID);

//��������
void CrabTaskResume(CrabByte TaskID);
void CrabTaskResumeFromISR(CrabByte TaskID);

//ϵͳ������
void CrabSystemTask();

//ͨѶ��������
void CrabCommandTask();

//�¼�����
void CrabEventTask();

//Ӧ������
void CrabApplicationTask();

//ע�ᾲ̬API����
void CrabRegisterStaticApi(); 

//ע��ʱ��API����
void CrabRegisterClockApi(); 

//ע����˿�API����
void CrabRegisterPortApi();

//ע�����API����
void CrabRegisterFuncApi();

//ע��MiCOר��API����
void CrabRegisterMicoApi();

//�������������״̬
void CrabChangeAppState(CrabByte State);

//����ϵͳLED��״̬
void CrabChangeLEDStatus(CrabByte Status);

//��������״̬
void CrabChangeBeep(CrabByte Width, CrabByte Count);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE