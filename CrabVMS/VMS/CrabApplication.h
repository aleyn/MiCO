/******************** Copyright wisearm.com *********************************
* File Name         : CrabApplication.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : Ӧ�ó���������
********************************************************************************/

#ifndef __CRAB_APP_MANAGE__
#define __CRAB_APP_MANAGE__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

//��ʼ�����������
void CrabApplicationInit();

//�������������״̬
void CrabChangeAppState(CrabByte State);

//Ӧ������
void CrabApplicationTask();

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE