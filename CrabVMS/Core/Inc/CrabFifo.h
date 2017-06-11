/******************** Copyright wisearm.com ************************************
* File Name         : CrabFifo.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �¼�FIFO������
********************************************************************************/

#ifndef __CRAB_FIFO__
#define __CRAB_FIFO__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define  CrabIntrEnable         0x8000
#define  CrabIntrDisable        0x0000
#define  CrabIntrBlockEnable    0x1000
#define  CrabIntrBlockDisable   0x2000
#define  CrabIntrActionCmd      0x4000
#define  CrabIntrActionEnable   0x4001
#define  CrabIntrActionDisable  0x4000
#define  CrabIntrAction         0x0001

#define  CrabIntrActionM    0xF7
#define  CrabIntrMask       0x7F
#define  CrabIntrExecute    0x88

//�¼�����
CrabBool CrabFifo_Config(CrabUShort IntrCmd);

//����¼�����
CrabBool CrabFifi_CheckIntr();

//�¼�ѹջ
CrabBool CrabFifo_PushEvent(CrabUint EventHandle);

//�¼���ջ
CrabBool CrabFifo_PopEvent(CrabUShort __var EventIndex);

//�¼���ջ���¼���ַ
CrabBool CrabFifo_PopFuncAddr(CrabUint __var FuncAddr);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE