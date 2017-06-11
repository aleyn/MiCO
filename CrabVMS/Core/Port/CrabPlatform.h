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

#ifdef  __ICCARM__  
#define __flash _Pragma("location=\".rodata\"")
#define __cache _Pragma("location=\".ccmram\"")
#define __ram   _Pragma("location=\".data\"")
#else
#define __flash
#define __cache
#define __ram
#endif

#ifdef __BORLANDC__
  #define CrabMemAlloc(a, b)  (a)malloc(b)    //�����ڴ�
  #define CrabMemFree(a)      free(a)         //�ͷ��ڴ�
  #define CrabMemFZero(a,b)   memset(a,0,b)   //�ڴ�����
  #define CrabMemFill(a,b,c)  memset(a,c,b)   //�ڴ����
  #define CrabMemCopy(a,b,c)  memcpy(a,b,c)   //�ڴ渴��
#else
  #define CrabMemAlloc(a, b)  (a)malloc(b)    //�����ڴ�
  #define CrabMemFree(a)      free(a)         //�ͷ��ڴ�
  #define CrabMemFZero(a,b)   memset(a,0,b)   //�ڴ�����
  #define CrabMemFill(a,b,c)  memset(a,c,b)   //�ڴ����
  #define CrabMemCopy(a,b,c)  memcpy(a,b,c)   //�ڴ渴��, ��IAR�У����ô˺�����Ҫ�� #include "string.h"
#endif

#ifdef __BORLANDC__
  #define strcasecmp          stricmp
  #define strncasecmp         strnicmp
  #define StrToInt            atoi            //�ַ���תΪ����
  #define StrToFloat          atof            //�ַ���תΪ������
  #define IntToStr            itoa            //����תΪ�ַ���
  #define FloatToStr          ftoa            //������תΪ�ַ���
#else
  #define strcasecmp          stricmp
  #define strncasecmp         strnicmp
  #define StrToInt            atoi            //�ַ���תΪ����
  #define StrToFloat          atof            //�ַ���תΪ������
  #define IntToStr            itoa            //����תΪ�ַ���
  #define FloatToStr          ftoa            //������תΪ�ַ���
#endif  

//ע��API����
void CrabRegisterApi();

//EVENT �¼�����
crabapi CrabEventIntr (CrabBool State);

//��׼����API
crabapi CrabInput (CrabUint Type, CrabAnsi Buffer, PCrabUint Length);

//��׼���API
crabapi CrabPrint (CrabAnsi Text, CrabUint Length, CrabBool LineEnd);

//��ʱAPI������
crabapi CrabDelay (CrabUint MSec);  
  
#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE