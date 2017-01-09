/******************** Copyright wisearm.com **********************************
* File Name         : CrabPlatform.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ƽ̨���
********************************************************************************/

#ifndef __CRAB_PLATFORM__
#define __CRAB_PLATFORM__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define CRAB_APP_OFF              0
#define CRAB_APP_STOPPING         1
#define CRAB_APP_LOADROM          2
#define CRAB_APP_RESET            3
#define CRAB_APP_ERROR            4
#define CRAB_APP_STANDBY          5
#define CRAB_APP_PAUSE            6
#define CRAB_APP_CONTINUE         7
#define CRAB_APP_STEP             8
#define CRAB_APP_RUNNING          9
#define CRAB_APP_EXCEPTION        0xFF

#ifdef __BORLANDC__
  #define CrabMemAlloc(a,b)   a = malloc(b)   //�����ڴ�
  #define CrabMemFree(a)      free(a)         //�ͷ��ڴ�
  #define CrabMemFZero(a,b)   memset(a,0,b)   //�ڴ�����
  #define CrabMemFill(a,b,c)  memset(a,c,b)   //�ڴ����
  #define CrabMemCopy(a,b,c)  memcpy(a,b,c)   //�ڴ渴��
#else
  #define CrabMemAlloc(a,b)   a = malloc(b)   //�����ڴ�
  #define CrabMemFree(a)      free(a)         //�ͷ��ڴ�
  #define CrabMemFZero(a,b)   memset(a,0,b)   //�ڴ�����
  #define CrabMemFill(a,b,c)  memset(a,c,b)   //�ڴ����
  #define CrabMemCopy(a,b,c)  memcpy(a,b,c)   //�ڴ渴��, ��IAR�У����ô˺�����Ҫ�� #include "string.h"
#endif  
  
#pragma pack(1)
typedef struct
{
  CrabPoint     Memory;         //�û��ڴ��ַ
  CrabUint      MemorySize;     //�û��ڴ��С
  CrabPoint     Cache;          //ָ�����
  CrabUint      CacheSize;      //ָ�������С
  CrabUint      FifoCount;      //�¼�FIFO����
} TCrabConfig, *PCrabConfig;

//ע��API����
void CrabRegisterApi();

//EVENT �¼�����
crabapi CrabEventIntr (CrabBool State);

//��׼����API
crabapi CrabInput (CrabUint Type, CrabAnsi Buffer, PCrabUint Length);

//��׼���API
crabapi CrabPrint (CrabAnsi Text, CrabUint Length);

//��ʱAPI������
crabapi CrabDelay (CrabUint MSec);  
  
#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE